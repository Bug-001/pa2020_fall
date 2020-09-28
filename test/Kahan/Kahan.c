#include <stdio.h>

float Kahan_sum(){
    float nums[40000];
    for(int i = 0; i < 40000; ++i){
        nums[i] = 0.1f;
    }
    float sum = 0;
    int c = 0;
    float num = 0.1f;
    float new_sum, term;
    for(int i = 0; i < 40000; ++i){
        // float term = nums[i] - c;
        float term = num - c;
        float new_sum = sum + term;
        c = (new_sum - sum) - term;
        sum = new_sum;
    }
    return sum;
}

float Acc_sum(){
    float nums[40000];
    float sum = 0;
    for(int i = 0; i < 40000; ++i){
        nums[i] = 0.1;
    }
    for(int i = 0; i < 40000; ++i){
        sum += nums[i];
    }
    return sum;
}

int main(){
    // TODO: 为什么自己的方法不对？为什么加-O优化可以使结果相对精确一些？
    printf("Kahan_sum = %f\n", Kahan_sum());
    printf("Acc_sum = %f\n", Acc_sum());
    float tem = 0.1f;
    float sum = tem;
    float c = 0;
    float y, t;
    int i;
    for(i=1; i<40000; i++){
        y = tem-c;
        t = sum+y;
        c = (t-sum)-y;
        sum = t;
    }
    printf("%f\n", sum);
    return 0;
}