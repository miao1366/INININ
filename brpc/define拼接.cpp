DEFINE_int32(port, 8010, "TCP Port of this server");

#define DEFINE_int32(name, val, txt) \
   DEFINE_VARIABLE(GFLAGS_NAMESPACE::int32, I, \
                   name, val, txt)

DEFINE_VARIABLE(GFLAGS_NAMESPACE::int32, I, port, 8010, "TCP Port of this server")


#define DEFINE_VARIABLE(type, shorttype, name, value, help)             \
  namespace fL##shorttype {                                             \
    static const type FLAGS_nono##name = value;                         \
    /* We always want to export defined variables, dll or no */         \
    GFLAGS_DLL_DEFINE_FLAG type FLAGS_##name = FLAGS_nono##name;        \
    type FLAGS_no##name = FLAGS_nono##name;                             \
    static GFLAGS_NAMESPACE::FlagRegisterer o_##name(                   \
      #name, MAYBE_STRIPPED_HELP(help), __FILE__,                       \
      &FLAGS_##name, &FLAGS_no##name);                                  \
  }                                                                     \
  using fL##shorttype::FLAGS_##name


  namespace fLI {                                             
    static const GFLAGS_NAMESPACE::int32 FLAGS_nonoport = 8010;                         
    GFLAGS_DLL_DEFINE_FLAG  GFLAGS_NAMESPACE::int32 FLAGS_port = FLAGS_nonoport;        
    GFLAGS_NAMESPACE::int32 FLAGS_noport = FLAGS_nonoport;                             
    static GFLAGS_NAMESPACE::FlagRegisterer o_port(                   
      "port", "TCP Port of this server", __FILE__,                      
      &FLAGS_port, &FLAGS_noport);                                  
  }                                                                     
  using fLI::FLAGS_port


DEFINE_string(certificate, "cert.pem", "Certificate file path to enable SSL");
#define DEFINE_string(name, val, txt)                                       \
  namespace fLS {                                                           \
    using ::fLS::clstring;                                                  \
    using ::fLS::StringFlagDestructor;                                      \
    static union { void* align; char s[sizeof(clstring)]; } s_##name[2];    \
    clstring* const FLAGS_no##name = ::fLS::                                \
                                   dont_pass0toDEFINE_string(s_##name[0].s, \
                                                             val);          \
    static GFLAGS_NAMESPACE::FlagRegisterer o_##name(                       \
        #name, MAYBE_STRIPPED_HELP(txt), __FILE__,                          \
        FLAGS_no##name, new (s_##name[1].s) clstring(*FLAGS_no##name));     \
    static StringFlagDestructor d_##name(s_##name[0].s, s_##name[1].s);     \
    extern GFLAGS_DLL_DEFINE_FLAG clstring& FLAGS_##name;                   \
    using fLS::FLAGS_##name;                                                \
    clstring& FLAGS_##name = *FLAGS_no##name;                               \
  }                                                                         \
  using fLS::FLAGS_##name


  namespace fLS {                                                           
    using ::fLS::clstring;                                                  
    using ::fLS::StringFlagDestructor;                                      
    static union { void* align; char s[sizeof(clstring)]; } s_certificate[2];    
    clstring* const FLAGS_nocertificate = ::fLS::                                
                                   dont_pass0toDEFINE_string(s_certificate[0].s, 
                                                             "cert.pem");          
    static GFLAGS_NAMESPACE::FlagRegisterer o_certificate(                       
        "certificate", "Certificate file path to enable SSL", __FILE__,                          
        FLAGS_nocertificate, new (s_certificate[1].s) clstring(*FLAGS_nocertificate));     
    static StringFlagDestructor d_certificate(s_certificate[0].s, s_certificate[1].s);     
    extern GFLAGS_DLL_DEFINE_FLAG clstring& FLAGS_certificate;                   
    using fLS::FLAGS_certificate;                                                
    clstring& FLAGS_ertificate = *FLAGS_nocertificate;                               
  }                                                                         
  using fLS::FLAGS_certificate

2. CHECK(false) << "This function should never be called, abort";

3. 