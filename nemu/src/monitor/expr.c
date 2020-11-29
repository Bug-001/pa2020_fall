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
	{"[0-9]{1,10}", NUM},
	{"\\+", ADD},
	{"\\-", SUB},
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
            else if(tokens[i - 1].type != NUM || tokens[i + 1].type != NUM)
            {
                tokens[i].type = DEREF;
            }
            break;
        case SUB:
        	if(i == 0)
            {
                tokens[i].type = NEG;
            }
            else if(tokens[i - 1].type != NUM || tokens[i + 1].type != NUM)
            {
                tokens[i].type = NEG;
            }
            break;
	    }
	}

	return true;
}

static bool check_parentheses(int p, int q, bool* success){
    return false;
}

static int eval(int p, int q, bool *success)
{
    if(p > q)
    {
        
    }
    else if(p == q)
    {
        
    }
    else if(check_parentheses(p, q) == true)
    {
        
    }
    else
    {
        
    }
}

uint32_t expr(char *e, bool *success)
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}
	return 0;
    //return eval(0, nr_token - 1, success);
}
