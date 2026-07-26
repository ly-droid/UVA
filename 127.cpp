#include<stack>
#include<list>
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
using ls = list<stack<string>> ;
ls ilist;
bool check(string a,string b)
{
    return a[0]==b[0] || a[1]==b[1];
}
int main()
{
    string temp;
    while(cin>>temp && temp!="#")
    {
        ilist.clear();
        stack<string> s;
        s.emplace(temp);
        ilist.emplace_back(s);
        for(int i=1;i<=51;i++)
        {
            cin>>temp;
            ilist.emplace_back(stack<string>());
            ilist.back().push(temp);
        }
        bool flag =false;
        auto ite =ilist.begin();
        for(++ite;ite!=ilist.end();)
        {
            string temp_now =ite->top();
            auto replace = ite,pos=ite,fir=ite;
            while(true) 
            {
                int count = 0;
                for(;;)
                {
                    if(pos--==ilist.begin())
                        break;
                    if(++count==3)
                        break;
                    if(count ==1)
                        fir=pos;
                }
                if(count ==3 && check(pos->top(),temp_now))
                {
                    replace = pos;
                    continue;
                }else if(count >=1 && check(fir->top(),temp_now))
                {
                    replace =fir;
                    pos=fir;
                    continue;
                }
                if(replace == ite)
                {
                    ++ite;
                    break;
                }
                replace->push(ite->top());
                ite->pop();
                flag = true; 
                if(ite->empty())
                    ilist.erase(ite);
                break;
            }
            if(flag)
            {
                flag = false;
                ite=ilist.begin();
                ++ite;
            }
        }
        int sum = ilist.size();
        cout<<sum<<(sum==1?" pile":" piles")<<" remaining:";
        for(auto ite =ilist.begin();ite!=ilist.end();++ite)
            cout<<" "<<ite->size();
        cout<<endl;
    }
    return 0;
}


