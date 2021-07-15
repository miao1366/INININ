1. DnsRoutine.cc
typedef unsigned short int sa_family_t;

#define	__SOCKADDR_COMMON(sa_prefix) \
  sa_family_t sa_prefix##family

struct sockaddr_un {
   __SOCKADDR_COMMON (sun_);
    char sun_path[108];		/* Path name.  */
};

struct sockaddr {
    SOCKADDR_COMMON (sa_);	/* Common data: address family and length.  */
    char sa_data[14];		/* Address data.  */
};

2. URIParser.cc
https://www.baidu.com/s?wd=postman%20uri&rsv_spt=1&rsv_iqid=0xfebadba0003fdd57&issp=1&f=8&rsv_bp=1&rsv_idx=2

https://www.baidu.com/s?wd=%E5%BC%A0%E5%9B%BD%E7%84%98&rsv_spt=1&rsv_iqid=0xb4d7af4600522027&issp=1&f=3&rsv_bp=1&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_dl=ts_3&rsv_enter=1&rsv_sug3=2&rsv_sug1=2&rsv_sug7=101&rsv_sug2=1&rsv_btype=i&prefixsug=%25E5%25BC%25A0&rsp=3&inputT=7660&rsv_sug4=8901

https://www.baidu.com/s?wd=%E5%BC%A0%E5%9B%BD%E7%84%98%2B2&rsv_spt=1&rsv_iqid=0xb4d7af4600522027&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&rqlang=cn&tn=baiduhome_pg&rsv_dl=tb&rsv_enter=1&oq=%25E5%25BC%25A0%25E5%259B%25BD%25E7%2584%2598&rsv_btype=t&inputT=2452&rsv_t=7bdfVjdupRr6NszsnM74JeoVYPUhz60L%2Bw3AJ265ccusq3HaNE2nF9OZE%2BwqPiEE6PtF&rsv_sug3=5&rsv_pq=b7ce0fd9002600c9&rsv_sug2=0&prefixsug=%25E5%25BC%25A0%25E5%259B%25BD%25E7%2584%2598%252B2&rsp=3&rsv_sug4=3112

在URI的path中，+号表示加号
在URI的query部分中，+号表示空格
空格编码为%20
空格(Space)的ASCII码值是:32
+号 ascii    43