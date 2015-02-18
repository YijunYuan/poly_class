#ifndef poly_class_H_INCLUDED
#define poly_class_H_INCLUDED
#include<map>
#include<cmath>
#include<typeinfo>
typedef long long unsigned ulong;
using namespace std;

template<typename T>
class poly_class
{
public:
    void inline             check_temp  (                ){
        temp_exist=false;
        if(temp.second!=0)
            core[temp.first]=temp.second;
        return ;
    };

                            poly_class  (                ){
        temp_exist=false;
    }

                            poly_class  (const poly_class<T>& a){
        //if(a.temp_exist)a.check_temp();
        core=a.core;
        temp_exist=a.temp_exist;
        temp=a.temp;
        if(temp_exist)check_temp();
    };

    ulong                   max_deg     (                ){
        if(temp_exist)check_temp();
        if(core.empty())return 0;
        typename map<ulong,T>::iterator p;
        p=core.end();p--;
        return p->first;
    };

    poly_class<T>&          operator =  (const poly_class<T>&  a){
        //if(a.temp_exist)a.check_temp();
        core=a.core;
        temp_exist=a.temp_exist;
        temp=a.temp;
        return (*this);
    };

    T&                      operator [] (ulong          n){
        if(temp_exist)check_temp();
        temp_exist=true;
        temp=make_pair(n,core[n]);
        return temp.second;
    };

    poly_class<T>           operator << (ulong          n){
        if(temp_exist)check_temp();
        typename map<ulong,T>::iterator p;
        poly_class res;
        for(p=core.begin();p!=core.end();p++){
            res.core[(p->first)+n]=p->second;
        }
        return res;
    };

    poly_class<T>           operator <<=(ulong          n){
        (*this)=(*this)<<n;
        return (*this);
    };

    poly_class<T>           operator >> (ulong          n){
        if(temp_exist)check_temp();
        typename map<ulong,T>::iterator p;
        poly_class res;
        if(core.empty())return res;
        p=core.end();p--;
        for(;p!=core.begin()&&p->first>=n;p--){
            res.core[(p->first)-n]=p->second;
        }
        if(core.begin()->first>=n)
            res.core[(core.begin()->first)-n]=core.begin()->second;
        return res;
    };

    poly_class<T>           operator >>=(ulong          n){
        (*this)=(*this)>>n;
        return (*this);
    };

    poly_class<T>   friend  operator +  (poly_class<T>  a,poly_class<T> b){
        ulong i,max=a.max_deg();
        if(max<b.max_deg())
            max=b.max_deg();
        poly_class<T> res;
        T coefft;
        for(i=0;i<=max;i++){
            coefft=a.core[i]+b.core[i];
            if(coefft!=0)
                res.core[i]=coefft;
        }
        return res;
    };

    poly_class<T>   friend  operator +  (poly_class<T>  a,T             v){
        if(a.temp_exist)a.check_temp();
        poly_class<T> res=a;//res[0]+=v;
        res[0]=res[0]+v;
        return res;
    };

    poly_class<T>   friend  operator +  (T              v,poly_class<T> a){
        if(a.temp_exist)a.check_temp();
        poly_class<T> res=a;//res[0]+=v;
        res[0]=res[0]+v;
        return res;
    };

    poly_class<T>           operator += (poly_class<T>  a){
        (*this)=(*this)+a;
        return (*this);
    };

    poly_class<T>           operator += (T              v){
        (*this)=(*this)+v;
        return (*this);
    };

    poly_class<T>   friend  operator -  (poly_class<T>  a,poly_class<T> b){
        ulong i,max=a.max_deg();
        if(max<b.max_deg())
            max=b.max_deg();
        poly_class<T> res;
        T coefft;
        for(i=0;i<=max;i++){
            coefft=a.core[i]-b.core[i];
            if(coefft!=0)
                res.core[i]=coefft;
        }
        return res;
    };

    poly_class<T>   friend  operator -  (poly_class<T>  a,T             v){
        if(a.temp_exist)a.check_temp();
        poly_class<T> res=a;//res[0]+=v;
        res[0]=res[0]-v;
        return res;
    };
/*
    poly_class<T>   friend  operator +  (T              v,poly_class<T> a){
        return a+v;
    };
*/

    poly_class<T>           operator -= (poly_class<T>  a){
        (*this)=(*this)-a;
        return (*this);
    };

    poly_class<T>           operator -= (T              v){
        (*this)=(*this)-v;
        return (*this);
    };

    poly_class<T>   friend  operator *  (poly_class<T>  a,T             v){
        if(a.temp_exist)a.check_temp();
        typename map<ulong,T>::iterator p;
        poly_class res;if(v==0)return res;
        for(p=a.core.begin();p!=a.core.end();p++){
            res.core[p->first]=v*(p->second);
        }
        return res;
    };

    poly_class<T>   friend  operator *  (T              v,poly_class<T> a){
        if(a.temp_exist)a.check_temp();
        typename map<ulong,T>::iterator p;
        poly_class res;if(v==0)return res;
        for(p=a.core.begin();p!=a.core.end();p++){
            res.core[p->first]=v*(p->second);
        }
        return res;
    };

    poly_class<T>   friend  operator *  (poly_class<T>  a,poly_class<T> b){
        T tmp;
        ulong i,j,a_max=a.max_deg(),b_max=b.max_deg();
        poly_class res;
        for(i=0;i<=a_max+b_max;i++){
            tmp=0;
            for(j=0;j<=i&&j<=a_max;j++){
                if(i-j<=b_max)
                    tmp+=a.core[j]*b.core[i-j];
            }
            if(tmp!=0)
                res.core[i]=tmp;

        }
        return res;
    };

    poly_class<T>           operator *= (poly_class<T>  a){
        (*this)=(*this)*a;
        return (*this);
    };

    poly_class<T>           operator *= (T              v){
        (*this)=(*this)*v;
        return (*this);
    };

    poly_class<T>   friend  operator /  (poly_class<T>  a,poly_class<T> b){
        poly_class res;ulong a_max=a.max_deg(),b_max=b.max_deg();
        if(a_max<b_max||b.core.empty())
            return res;
        if(b_max==0)
            return a/b[0];
        T tmp=b.core[b_max];
        while(a_max>=b_max){
            res.core[a_max-b_max]=a.core[a_max]/tmp;
            a-=a.core[a_max]/tmp*(b<<(a_max-b_max));
            a_max=a.max_deg();
        }
        return res;
    };

    poly_class<T>   friend  operator /  (poly_class<T>  a,T             v){
        if(a.temp_exist)a.check_temp();
        typename map<ulong,T>::iterator p;
        poly_class res;//if(v==0)return res;
        for(p=a.core.begin();p!=a.core.end();p++){
            res.core[p->first]=(p->second)/v;
        }
        return res;
    };

    poly_class<T>           operator /= (poly_class<T>  a){
        (*this)=(*this)/a;
        return (*this);
    };

    poly_class<T>           operator /= (T              v){
        return (*this)/v;
    };

    poly_class<T>   friend  operator %  (poly_class<T>  a,poly_class<T> b){
        poly_class res;ulong a_max=a.max_deg(),b_max=b.max_deg();
        if(a_max<b_max||b.core.empty())
            return res;
        if(b_max==0)
            return a/b[0];
        T tmp=b.core[b_max];
        while(a_max>=b_max){
            res.core[a_max-b_max]=a.core[a_max]/tmp;
            a-=a.core[a_max]/tmp*(b<<(a_max-b_max));
            a_max=a.max_deg();
        }
        return a;
    };

    poly_class<T>           operator %= (poly_class<T>  a){
        (*this)=(*this)%a;
        return (*this);
    };

    bool            friend  operator == (poly_class<T>  a,poly_class<T> b){
        if(a.temp_exist)a.check_temp();
        if(b.temp_exist)b.check_temp();
        return a.core==b.core;
    };

    bool            friend  operator != (poly_class<T>  a,poly_class<T> b){
        if(a.temp_exist)a.check_temp();
        if(b.temp_exist)b.check_temp();
        return a.core!=b.core;
    };

    T                       value       (T              v){
        ulong max=max_deg();
        if(max==0)return core[0];
        T res=core[max];
        for(ulong i=max-1;i!=0;i--){
            res=res*v+core[i];
        }
        res=res*v+core[0];
        return res;
    };

    poly_class<T>           derivative  (                ){
        typename map<ulong,T>::iterator p=core.begin();
        poly_class res;
        if(max_deg()<2){
            res.core[0]=core[1];
            return res;
        }
        if(p->first==0)p++;

        for(;p!=core.end();p++){
            res.core[p->first-1]=p->second*p->first;
        }
        return res;
    };

    T                       root        (                ){
        poly_class der=derivative();
        T res=2.71828182845904,tmp=res+1;
        ulong count=0;
        while(abs(tmp-res)>=0.00000000001&&count<=10000){
            tmp=res;
            res=res-(*this).value(res)/der.value(res);
            count++;
        }
        return res;
    };

    T                       root        (T              v){
        poly_class der=derivative();
        T res=v,tmp=res+1;
        ulong count=0;
        while(abs(tmp-res)>=0.00000000001&&count<=10000){
            tmp=res;
            res=res-(*this).value(res)/der.value(res);
            count++;
        }
        return res;
    };

    poly_class<T>   friend  pow         (poly_class<T>  a,ulong         n){
        if(a.temp_exist)a.check_temp();
        poly_class<T> res;
        res.core[0]=1;
        while (n){
            if (n&1){
                res=res*a;
                --n;
            }
            else{
                a=a*a;
                n>>=1;
            }
        }
        return res;
    };

    poly_class<T>   friend  powmod      (poly_class<T>  a,ulong         n,poly_class<T>  m){
        if(a.temp_exist)a.check_temp();
        if(m.temp_exist)m.check_temp();
        poly_class<T> res;
        res.core[0]=1;
        while (n){
            if (n&1){
                res=res*(a%m);
                --n;
            }
            else{
                a=a*a%m;
                n>>=1;
            }
        }
        return res;
    };

    friend istream&         operator  >>(istream&      in,poly_class<T>&a){};

    friend ostream&         operator  <<(ostream&     out,poly_class<T> a){
        if(a.temp_exist)a.check_temp();
        ulong i=0;
        out<<'[';
        for(;i<a.max_deg();i++){
            out<<a.core[i]<<' ';
        }
        out<<a.core[i]<<"]\n";
        return out;
    };
private:
    map<ulong,T>core;
    pair<ulong,T>temp;
    bool temp_exist;
};

#endif // poly_class_H_INCLUDED
