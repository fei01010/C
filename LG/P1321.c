#include<stdio.h>
#include<string.h>

static int count_boy(const char *s){
    int n = (int)strlen(s);
    int cnt = 0;
    for (int i = 0; i < n; ){
        if (i + 2 < n && s[i] == 'b' && s[i + 1] == 'o' && s[i + 2] == 'y'){
            cnt++;
            i += 3;
        }else if (i + 1 < n && s[i] == 'b' && s[i + 1] == 'o'){
            cnt++;
            i += 2;
        }else if (i + 1 < n && s[i] == 'o' && s[i + 1] == 'y'){
            cnt++;
            i += 2;
        }else if (s[i] == 'b' || s[i] == 'o' || s[i] == 'y'){
            cnt++;
            i += 1;
        }else{
            i += 1;
        }
    }
    return cnt;
}

static int count_girl(const char *s){
    int n = (int)strlen(s);
    int cnt = 0;
    for (int i = 0; i < n; ){
        if (i + 3 < n && s[i] == 'g' && s[i + 1] == 'i' && s[i + 2] == 'r' && s[i + 3] == 'l'){
            cnt++;
            i += 4;
        }else if (i + 2 < n && s[i] == 'g' && s[i + 1] == 'i' && s[i + 2] == 'r'){
            cnt++;
            i += 3;
        }else if (i + 2 < n && s[i] == 'i' && s[i + 1] == 'r' && s[i + 2] == 'l'){
            cnt++;
            i += 3;
        }else if (i + 1 < n && s[i] == 'g' && s[i + 1] == 'i'){
            cnt++;
            i += 2;
        }else if (i + 1 < n && s[i] == 'i' && s[i + 1] == 'r'){
            cnt++;
            i += 2;
        }else if (i + 1 < n && s[i] == 'r' && s[i + 1] == 'l'){
            cnt++;
            i += 2;
        }else if (s[i] == 'g' || s[i] == 'i' || s[i] == 'r' || s[i] == 'l'){
            cnt++;
            i += 1;
        }else{
            i += 1;
        }
    }
    return cnt;
}

int main(){
    char s[300];
    if (!fgets(s, sizeof(s), stdin)){
        return 0;
    }
    int len = (int)strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')){
        s[--len] = '\0';
    }

    int boy = count_boy(s);
    int girl = count_girl(s);

    printf("%d\n", boy);
    printf("%d\n", girl);
    return 0;
}



//思路1：
//统计b,o,y和g,i,r,l的个数,分别取最大值
//排除

//思路2：
//找到boy,girl数量加1，改为句号
//找到bo,oy,gir,irl,gi,ir,rl
//找到b,o,y,g,i,r,l数量加1，改为句号 