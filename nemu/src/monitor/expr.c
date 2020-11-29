#include "nemu.h"
#include "cpu/reg.h"
#include "memory/memory.h"

#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum
{
	NOTYPE = 256,
	
	ADD,
	SUB,
	MUL,
	DIV,
	NEG,
	
	EQ,
	NEQ,
	
	LPAR,
	RPAR,
	
	AND,
	OR,
	NOT,
	
	DEREF,
	
	NUM,
	REG,
	SYMB

	/* TODO: Add more token types */

};

static struct rule
{
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +", NOTYPE}, // white space
	{"[0-9]{1,10}|0[xX][0-9a-fA-F]{1,8}", NUM},
	{"\\+", ADD},
	{"-", SUB},
	{"\\*", MUL},
	{"/", DIV},
	
    {"==", EQ},
    {"\\!=", NEQ},
    
    {"\\(", LPAR},
    {"\\)", RPAR},
    
    {"&&", AND},
    {"\\|\\|", OR},
    {"\\!={0}", NOT},
    
    {"\\$[a-z]{1,31}", REG},
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]))

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
	int i;
	char error_msg[128];
	int ret;

	for (i = 0; i < NR_REGEX; i++)
	{
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if (ret != 0)
		{
			regerror(ret, &re[i], error_msg, 128);
			assert(ret != 0);
		}
	}
}

typedef struct token
{
	int type;
	char str[32];
} Token;

static Token tokens[32];
static int nr_token;

static bool make_token(char *e)
{
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;

	while (e[position] != '\0')
	{
		/* Try all rules one by one. */
		for (i = 0; i < NR_REGEX; i++)
		{
			if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
			{
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				printf("match regex[%d] at position %d with len %d: %.*s\n", i, position, substr_len, substr_len, substr_start);
				fflush(stdout);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch (rules[i].token_type)
				{
				case NOTYPE:
				    break;
				case NUM:
				case REG:
				    *tokens[nr_token].str = 0;
				    strncat(tokens[nr_token].str, substr_start, substr_len);
				default:
					tokens[nr_token].type = rules[i].token_type;
					nr_token++;
				}

				break;
			}
		}

		if (i == NR_REGEX)
		{
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
	
	for(int i = 0; i < nr_token; ++i)
	{
	    switch(tokens[i].type)
	    {
        case MUL:
            if(i == 0)
            {
                tokens[i].type = DEREF;
            }
            else if(tokens[i - 1].type != NUM)
            {
                tokens[i].type = DEREF;
            }
            break;
        case SUB:
        	if(i == 0)
            {
                tokens[i].type = NEG;
            }
            else if(tokens[i - 1].type != NUM)
            {
                tokens[i].type = NEG;
            }
            break;
	    }
	}

	return true;
}

static bool parentheses_match(int p, int q)
{
    int match = 0;
    for(int i = p; i <= q; ++i)
    {
        if(tokens[i].type == LPAR) ++match;
        else if(tokens[i].type == RPAR) --match;
        if(match < 0) return false;
    }
    if(match != 0) return false;
    else return true;
}

static bool parentheses_probe(int p, int q)
{
    if(tokens[p].type == LPAR && tokens[q].type == RPAR) return true;
    else return false;
}

static bool check_parentheses(int p, int q, bool* success)
{
    bool ok = parentheses_match(p, q);
    if(ok)
    {
        bool strip_ok = parentheses_probe(p, q) && parentheses_match(p + 1, q - 1);
        if(strip_ok) return true;
        else return false;
    }
    else
    {
        *success = false;
        return false;
    }
}

static int pri(int type)
{
    switch(type)
    {
        case LPAR:
        case RPAR:
            return 1;
            
        case NOT:
        case DEREF:
        case NEG:
            return 2;
            
        case MUL:
        case DIV:
            return 3;
            
        case ADD:
        case SUB:
            return 4;
            
        case EQ:
        case NEQ:
            return 7;
        
        case AND:
            return 11;
            
        case OR:
            return 12;
        
        default:
            return 0;
    }
}

static int dominant_operator(int p, int q, bool *success)
{
    int res = p;
    int res_pri = pri(tokens[res].type);
    int in_par = 0;
    for(int i = p + 1; i <= q; ++i)
    {
        if(tokens[i].type == LPAR) ++in_par;
        else if(tokens[i].type == RPAR) --in_par;
        else if(in_par == 0)
        {
            int temp = pri(tokens[i].type);
            if(temp >= res_pri)
            {
                res = i;
                res_pri = temp;
            }
        }
    }
    return res;
}

static uint32_t calculate_1op(int op, uint32_t val, bool *success)
{
    switch(op)
    {
        case NEG: return -val;
        case DEREF: return vaddr_read(val, 0, 4); // DEBUG: sreg
        default: *success = false; return 0;
    }
}

static uint32_t calculate_2op(uint32_t val1, int op, uint32_t val2, bool *success)
{
    switch(op)
    {
        case ADD: return val1 + val2;
        case SUB: return val1 - val2;
        case MUL: return val1 * val2;
        case DIV: return val1 / val2;
        case AND: return val1 && val2;
        case OR: return val1 || val2;
        case EQ: return val1 == val2;
        case NEQ: return val1 != val2;
        default: *success = false; return 0;
    }
}

static uint32_t eval(int p, int q, bool *success)
{
    if(p > q)
    {
        *success = false;
        return 0;
    }
    else if(p == q)
    {
        switch(tokens[p].type)
        {
            case NUM: 
                char* format;
                if(tokens[p].str[1] == 'x') format = "%x";
                else if(tokens[p].str[1] == 'X') format = "%X";
                else format = "%d";
                int num;
                sscanf(tokens[p].str, format, &num);
                return num;
            case REG: return get_reg_val(tokens[p].str + 1, success);
            default: *success = false; return 0;
        }
    }
    else if(check_parentheses(p, q, success) == true)
    {
        return eval(p + 1, q - 1, success); 
    }
    else
    {
        int op = dominant_operator(p, q, success);
        printf("op == %d\n", op);
        fflush(stdout);
        if(tokens[op].type == NEG || tokens[op].type == DEREF)
        {
            uint32_t val = eval(op + 1, q, success);
            return calculate_1op(tokens[op].type, val, success);
        }
        else if(tokens[op].type == NUM || tokens[op].type == REG)
        {
            *success = false;
            return 0;
        }
        else
        {
            uint32_t val1 = eval(p, op - 1, success);
            uint32_t val2 = eval(op + 1, q, success);
            return calculate_2op(val1, tokens[op].type, val2, success);
        }
    }
}

uint32_t expr(char *e, bool *success)
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}
	printf("nr_token == %d\n", nr_token);
    return eval(0, nr_token - 1, success);
}
