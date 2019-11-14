#include<iostream>
#include<string.h>
#include<list>
#include<iomanip>
using namespace std;
#define c109 1000000000
typedef unsigned long long int ulli;
struct bigint{
    list<int> ptr;   //points to array where number is stored
};


class operate{
public:
    list<int> hash[10];
    struct bigint add(struct bigint ip1,struct bigint ip2)
    {
        list<int> result;
        int size1 = ip1.ptr.size();
        int size2 = ip2.ptr.size();
        int ressize=0;
        char carry=0;
        if(size1>size2)
        {
            //ip1 is > ip2
            auto it1 = ip1.ptr.rbegin();
            auto it2 = ip2.ptr.rbegin();
            while(size2--)
            {
                int res = (*it1)+(*it2)+carry;
                if(res>9)
                {
                    carry = 1;
                    res = res%10;
                    result.push_front(res);
                    ressize++;
                }else
                {
                    carry = 0;
                    result.push_front(res);
                    ressize++;
                }
                it1++;
                it2++;
            }
            size1 = ip1.ptr.size() - ip2.ptr.size();
            while(size1--)
            {
                int res = (*it1)+carry;
                if(res>9)
                {
                    carry = 1;
                    res = res%10;
                    result.push_front(res);
                    ressize++;
                }else{
                    carry=0;
                    result.push_front(res);
                    ressize++;
                }
                it1++;
            }
            if(carry)
            {
                result.push_front(carry);
                ressize++;
            }
        }else{
            if(size1 == size2)
            {
                auto it1 = ip1.ptr.rbegin();
                auto it2 = ip2.ptr.rbegin();
                while(size2--)
                {
                    int res = (*it1)+(*it2)+carry;
                    if(res>9)
                    {
                        carry = 1;
                        res = res%10;
                        result.push_front(res);
                        ressize++;
                    }else
                    {
                        carry = 0;
                        result.push_front(res);
                        ressize++;
                    }
                    it1++;
                    it2++;
                }
                if(carry)
                {
                    result.push_front(carry);
                    ressize++;
                }
            }else{
                if(size1<size2)
                {
                    auto it1 = ip1.ptr.rbegin();
                    auto it2 = ip2.ptr.rbegin();
                    while(size1--)
                    {
                        int res = (*it1)+(*it2)+carry;
                        if(res>9)
                        {
                            carry = 1;
                            res = res%10;
                            result.push_front(res);
                            ressize++;
                        }else
                        {
                            carry = 0;
                            result.push_front(res);
                            ressize++;
                        }
                        it1++;
                        it2++;
                    }
                    size2 = ip2.ptr.size() - ip1.ptr.size();
                    while(size2--)
                    {
                        int res = (*it2)+carry;
                        if(res>9)
                        {
                            carry = 1;
                            res = res%10;
                            result.push_front(res);
                            ressize++;
                        }else{
                            carry=0;
                            result.push_front(res);
                            ressize++;
                        }
                        it2++;
                    }
                    if(carry)
                    {
                        result.push_front(carry);
                        ressize++;
                    }
                }
            }
        }
        bigint resultp;
        resultp.ptr = result;
        return resultp;
    }



     struct bigint divideby2(struct bigint ip2)
     {
         auto it = ip2.ptr.rbegin();
         list<int> result;
         result.push_front(*it/2);
         auto it1 = result.rbegin();
         it++;
         int ressize = 0;
         while(it!=ip2.ptr.rend())
         {
             if((*it)%2 == 1)
             {
                 *(it1) = *(it1) + 5;
                 result.push_front(*(it)/2);
                 ressize++;
             }else{
                 result.push_front(*(it)/2);
                 ressize++;
             }
             it++;
             it1++;
         }
         while(result.front()==0)
            result.pop_front();
         bigint resultp;
         resultp.ptr = result;
         return resultp;
     }

     void testHash()
     {
         for(int i=0;i<10;i++)
         {
             auto it = hash[i].begin();
             while(it!=hash[i].end())
                 cout<<*it++;
            cout<<endl;
         }
     }

     void setHash(bigint ip1)
     {
         for(int i=0;i<10;i++)
         {
             hash[i] = multiplywithsingle(ip1.ptr,i);
         }
     }
     list<int> multiplywithsingle(list<int> input,int dig)
     {
         auto it1 = input.rbegin();
         list<int> result;
         int temp = (*it1)*dig;
         result.push_front(temp%10);
         int carry = temp/10;
         it1++;
         while(it1!=input.rend())
         {
             temp = (*it1)*dig;
             temp = temp+carry;
             result.push_front(temp%10);
             carry = temp/10;
             it1++;
         }
         if(carry)
            result.push_front(carry);
        return result;
     }

     struct bigint multiply(struct bigint ip1, struct bigint ip2)
     {
         setHash(ip1);
         auto it = ip2.ptr.begin();
         int sizeofip2 = ip2.ptr.size();
         sizeofip2--;
         struct bigint result;
         list<int> zero;
         zero.push_back(0);
         result.ptr = zero;
         struct bigint temp;
         while(it!=ip2.ptr.end())
         {
             temp = append(hash[*it],sizeofip2,0);
             result = add(result,temp);
             sizeofip2--;
             it++;
         }
         return result;
     }
     struct bigint append( list<int> ip,int count,int dig)
     {
         while(count--)
         {
             ip.push_back(dig);
         }
         struct bigint result;
         result.ptr = ip;
         return result;
     }

     void testMultiply(struct bigint ip1,struct bigint ip2)
     {
         struct bigint result;
         result = multiply(ip1,ip2);
         auto it1 = result.ptr.begin();
         while(it1!=result.ptr.end())
            cout<<*it1++;
     }
     bool iszero(struct bigint ip)
     {
         auto it = ip.ptr.begin();
         while(it!=ip.ptr.end())
         {
             if(*it!=0)
                return false;
             it++;
         }
         return true;
     }
     bool isone(struct bigint ip)
     {
         auto it = ip.ptr.rbegin();
         if(*it!=1)
            return false;
        it++;
         while(it!=ip.ptr.rend())
         {
             if(*it!=0)
                return false;
             it++;
         }
         return true;
     }

     bool iseven(struct bigint ip)
     {
         auto it = ip.ptr.rbegin();
         if(*it%2==0)
            return true;
        else
            return false;
        return false;
     }

     struct bigint temppow(struct bigint x, struct bigint y)
     {
         if(iszero(y))
        {
            struct bigint result;
            list<int> one;
            one.push_back(1);
            result.ptr = one;
            return result;
        }
        if(isone(y))
        {
            return x;
        }
        if(iseven(y))
        {
            struct bigint temp = temppow(x,divideby2(y));
            return multiply(temp,temp);
        }
        if(!iseven(y))
        {
            struct bigint temp;
            struct bigint temp2 = temppow(x,divideby2(y));
            temp = multiply(temp2,temp2);
            return multiply(temp,x);
        }
     }

     bool isequal(struct bigint ip1,struct bigint ip2)
     {
         auto it1 = ip1.ptr.rbegin();
         auto it2 = ip2.ptr.rbegin();
         while((it1!=ip1.ptr.rend()) && (it2!=ip2.ptr.rend()))
         {
             if(*it1 != *it2)
                return false;
             it1++;
             it2++;
         }
         if(ip1.ptr.size() == ip2.ptr.size())
            return true;
        return false;
     }

     struct bigint subtract(struct bigint ip1,struct bigint ip2)
     {
         struct bigint ip2comp = getComp(ip1,ip2);
         auto it1 = ip2comp.ptr.begin();
         struct bigint zero;
         zero.ptr.push_back(0);
         if(isequal(ip1,ip2))
            return zero;
        struct bigint temp = add(ip1,ip2comp);
        struct bigint one;
        list<int> on;
        on.push_back(1);
        one.ptr = on;
        if(temp.ptr.size() > ip1.ptr.size())
        {
            temp.ptr.pop_front();
            temp = add(temp,one);
        }
        auto it2 = temp.ptr.begin();
        while(*it2++ == 0)
            temp.ptr.pop_front();
        if(iszero(temp))
            return zero;
        return temp;
     }
     struct bigint getComp(struct bigint ip1, struct bigint ip2)
     {
         int size1 = ip1.ptr.size();
        struct bigint result;
        list<int> temp;
        auto it2 = ip2.ptr.rbegin();
        while(it2!=ip2.ptr.rend())
        {
            int tem = 9 - (*it2);
            temp.push_front(tem);
            it2++;
            size1--;
        }
        while(size1--)
        {
            temp.push_front(9);
        }
        result.ptr = temp;
        return result;
     }

     int greater(struct bigint ip1,struct bigint ip2)
     {
         if(ip1.ptr.size() > ip2.ptr.size())
            return 1;
        if(ip1.ptr.size() < ip2.ptr.size())
            return -1;
        auto it1 = ip1.ptr.begin();
        auto it2 = ip2.ptr.begin();
        while(it1!=ip1.ptr.end())
        {
            if(*it1 > *it2)
                return 1;
            if(*it1 < *it2)
                return -1;
            it1++;
            it2++;
        }
        return 0;
     }

     struct bigint getmod(struct bigint ip1,struct bigint ip2)
     {

         int diff,size1,size2;
         struct bigint temp;
         struct bigint zero;
         zero.ptr.push_back(0);
         while(greater(ip1,ip2)!=-1)
         {
             size1 = ip1.ptr.size();
             size2 = ip2.ptr.size();
             diff = size1-size2-1;
             if(diff>-1)
                temp = append(ip2.ptr,diff,0);
            else
                temp = ip2;
             ip1 = subtract(ip1,temp);
             if(iszero(ip1))
                return zero;
         }
        auto it1 = ip1.ptr.begin();
        return ip1;
     }
     struct bigint getgcd(struct bigint ip1,struct bigint ip2)
     {
         if(iszero(ip1))
             return ip2;
         return getgcd(getmod(ip2,ip1),ip1);
     }
};

struct bigint getstruct(string x)
{
    struct bigint big1;
    list<int> ip1;
    for(int i=0;i<x.size();i++)
    {
        ip1.push_back(x[i]-'0');
    }
    if(x[0]=='-')
    {
        ip1.pop_front();
        big1.ptr = ip1;
    }
    else
    {
        big1.ptr = ip1;
    }
    return big1;
}

char* power(string x,string y)
{
    struct bigint big1 = getstruct(x);
    struct bigint big2 = getstruct(y);
    struct bigint result;
    operate op;
    result = op.temppow(big1,big2);
    auto it1 = result.ptr.begin();
    if(x[0] == '-' && !op.iseven(big2))
        cout<<"-";
    while(it1!= result.ptr.end())
        cout<<*it1++;
    cout<<endl;
}

char* gcd(string x,string y)
{
    struct bigint big1 = getstruct(x);
    struct bigint big2 = getstruct(y);
    struct bigint result;
    operate op;
    if(big1.ptr.size()<big2.ptr.size())
        result = op.getgcd(big2,big1);
    else
        result = op.getgcd(big1,big2);
    auto it1 = result.ptr.begin();
    while(it1!=result.ptr.end())
        cout<<*it1++;
    cout<<endl;
}

char* fact(int x)
{
    int loopcount = x;
    ulli result[500000];   //ceil of 1000/9
    for(int i=0;i<500000;i++)
        result[i] = 0;
    ulli temp=1;
    result[0]=1;
    int valid=0;
    int counter = 1;
    ulli carryover = 0;
    int i;
    while(loopcount--)
    {
        i=0;
        while(i<=valid)
        {
            temp = result[i]*counter;
            temp = temp + carryover;
            carryover=0;
            if(temp<c109)
            {
                result[i] = temp;
            }else{
                result[i] = temp%c109;
                carryover = temp/c109;
                if(i==valid)
                    valid++;
            }
            i++;
        }
        counter++;
    }
    cout<<result[valid];
    for(int i=valid-1;i>=0;i--)
    {
        cout<<setfill('0')<<setw(9)<<result[i];
    }
    cout<<endl;
}

void printmenu()
{
    cout<<"Enter operation to be performed"<<endl;
    cout<<"1. Pow(x,y)"<<endl;
    cout<<"2. gcd(x,y)"<<endl;
    cout<<"3. Fact(x)"<<endl;
}

int main()
{
    string x;
    string y;
    int fac;
    int choice;
    int t;
    cin>>t;
    while(t--)
    {
        //printmenu();
        cin>>choice;
        switch(choice)
        {
            case 1 :
            {
                cin>>x;
                cin>>y;
                power(x,y);
            }
            break;
            case 2 :
            {
                cin>>x;
                cin>>y;
                gcd(x,y);
            }
            break;
            case 3 :
            {
                cin>>fac;
                fact(fac);
            }
            break;
            default :
            {

            }
        }
    }
    return 0;
}
