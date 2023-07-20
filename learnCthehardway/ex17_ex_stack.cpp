#include <stdio.h>

class Stack{
    private:
        int top=0;
        int s[100]={0};
    public:
        int gettop(){
            return top;
        }
        void push(int x){
            s[top++] = x;
        }
        int pop(){
            if(!top) return -1;
            return s[--top];
        }
};

int main(int argc,char *argv[])
{
    Stack st;
    while(1){
        char opt;
        scanf("%c",&opt);
        switch (opt)
        {
        case 'u':
            int num;
            scanf("%d",&num);
            st.push(num);
            break;
        case 'p':
            printf("%d\n",st.pop());
            break;
        default:
            break;
        }
    }
    return 0;
}