//
//  올바른 괄호 문자열
//  3012.cpp
//  AlgoriGym
//
//  Created by nicewoong on 2018. 4. 9..
//  Copyright © 2018년 nicewoong. All rights reserved.
//  https://www.acmicpc.net/problem/3012
//  https://gist.github.com/Baekjoon/8ba00d0064e8ca9c65f9ce8d64be5626

// 문제에서 5자리가 넘어가는 경우는 끝 5자리만 출력하라고 되어있습니다.
// 또한 5인 경우와 1000000000005 인 경우에는 각각 5와 00005로 출력해야 함에 유의하세요

#include <cstdio>
#include <iostream>
#define MAX_N 200  // 2~200
#define MOD 100000  // 다섯자리

using namespace std;


char A[MAX_N + 1] = {0}; // ( [ { ? 중 하나가 저장됨.
char left_braket[] = {'(', '[', '{'};
char right_braket[] = {')', ']', '}'};
long long d[MAX_N + 1][MAX_N + 1];
bool over_5 = false;

void init_memoization(int N) {
    for(int i=0; i<= N; i++ ) {
        for(int j=0; j<= N; j++) {
            d[i][j] = -1;
        }
    }
}


long long get_counts(int i, int j) {
    
    if(i>j)
        return 1;

    
    if(d[i][j] > -1) // memoization
        return d[i][j];
    
    
    long long sum_of_cur_count = 0;
    
    // if 에 하나도 안 맞을 경우 최종적으로는 sum_of_cur_count = 0 반환
    int cur_index = i;
    for(int k=i+1; k<= j ; k= k+2) {
        for(int index_of_bracket = 0; index_of_bracket<=2; index_of_bracket++) {
            
            if(A[cur_index] == left_braket[index_of_bracket] || A[cur_index] == '?') {
                if(A[k] == right_braket[index_of_bracket] || A[k] == '?') {
                    
                    long long temp = get_counts(i+1, k-1) * get_counts(k+1, j);
                    
                    sum_of_cur_count += temp;
                    
                    if(sum_of_cur_count > MOD)
                        over_5= true;

                    sum_of_cur_count%=MOD;
                    
                    
                }
            }// end of outer if
            
        }
    }// end of outer for
    
    d[i][j] = sum_of_cur_count; // save memoization
    return d[i][j];
    
}// end of func


int main() {
    
    
    int N;
    
    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> A[i];
    }
    init_memoization(N);
    long long ans = get_counts(1, N);
    if(over_5)
        printf("%05lld\n", ans);
    else
        cout << ans << endl;
    
    return 0;
}
