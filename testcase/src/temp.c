//#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
char *tokens;
int len = 0;
int pre_check_parentheses(int p, int q)
{
    int num = 0;
    for(int i = p; i <= q; i++)
    {
        if(tokens[i] == '(')
            num++;
        if(tokens[i] == ')')
            num--;
        if (num < 0)
            return 0;
    }
    return !num;
}

int check_parentheses(int p, int q)
{
    if(pre_check_parentheses(p, q))
    {    
        if(tokens[p] == '(' && tokens[q] == ')')
            return pre_check_parentheses(p + 1, q - 1);
        else
            return 0;
    }
    else
		return -1;
}
int find_op(int p, int q)
{
    int op = p, parentheses = 0, pr = 1;
    for(int i = p; i <= q; i++)
    {
        if (tokens[i] == '(')
        {
            parentheses++;
            continue;
        }
        if (tokens[i] == ')')
        {
            parentheses--;
            continue;
        }
        if (parentheses != 0)
            continue;
        else if (tokens[i] == '+' || tokens[i] == '-')
        {
            op = i;
            pr = 0;
        }
		else if ((tokens[i] == 'x' || tokens[i] == '/') && pr == 1)
			op = i;
    }

}
long long eval(int p, int q)
{
	if (p > q)
        return 0;
    else if (p == q)
        return tokens[p] - '0';
    else if (check_parentheses(p, q) == 1)
        return eval(p + 1, q - 1);
    else
    {
        int op = find_op(p, q);
//		printf("p = %d, op - 1 = %d, op + 1 = %d, q = %d\n", p, op - 1, op + 1, q);
        long long val1 = eval(p, op - 1);
        long long val2 = eval(op + 1, q);
//		printf("op == %d, type == %c, val1 = %lld, val2 = %lld\n", op, tokens[op], val1, val2);
        switch (tokens[op])
        {
			case '+':
                return val1 + val2;
            case '-':
                return val1 - val2;
            case 'x':
                return val1 * val2;
            case '/':
                return val1 / val2;
			default:
				return 0;
		}
	}
}
int main(void)
{
	tokens = (char *)malloc(sizeof(char) * 128);
	scanf("%s", tokens);
	int len = 0;
	while(tokens[len++] != '\0');
	printf("%lld\n", eval(0, len - 2));
	return 0;
}
