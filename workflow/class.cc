1 class ComplexHttpTask : public WFComplexClientTask<HttpRequest, HttpResponse>;    HttpTaskImpl.cc
    ComplexHttpTask(int redirect_max,
					int retry_max,
					http_callback_t&& callback):
		WFComplexClientTask(retry_max, std::move(callback)),
		redirect_max_(redirect_max),
		redirect_count_(0)
	{
		HttpRequest *client_req = this->get_req();

		client_req->set_method(HttpMethodGet);
		client_req->set_http_version("HTTP/1.1");
	}
    {
        int redirect_max_;
	    int redirect_count_;
    }
    using WFHttpTask = WFNetworkTask<protocol::HttpRequest,protocol::HttpResponse>;

2 template<class REQ, class RESP, typename CTX = bool>
  class WFComplexClientTask : public WFClientTask<REQ, RESP>                        WFTaskFactory.inl
    
    WFComplexClientTask(int retry_max, task_callback_t&& cb):
		WFClientTask<REQ, RESP>(NULL, WFGlobal::get_scheduler(), std::move(cb))
	{
		type_ = TT_TCP;
		fixed_addr_ = false;
		retry_max_ = retry_max;
		retry_times_ = 0;
		redirect_ = false;
		ns_policy_ = NULL;
		router_task_ = NULL;
	}
    {
        TransportType type_;
	    ParsedURI uri_;
	    std::string info_;
	    bool fixed_addr_;
	    bool redirect_;
	    CTX ctx_;
	    int retry_max_;
	    int retry_times_;
	    WFNSPolicy *ns_policy_;
	    WFRouterTask *router_task_;
	    RouteManager::RouteResult route_result_;
	    void *cookie_;
    }

3 class WFClientTask : public WFNetworkTask<REQ, RESP>                              WFTask.inl
  WFClientTask(CommSchedObject *object, CommScheduler *scheduler,
				 std::function<void (WFNetworkTask<REQ, RESP> *)>&& cb) :
		WFNetworkTask<REQ, RESP>(object, scheduler, std::move(cb))
	{

	}
    {

    }

4 template<class REQ, class RESP>
  class WFNetworkTask : public CommRequest                                          WFTask.h
  WFNetworkTask(CommSchedObject *object, CommScheduler *scheduler,
				  std::function<void (WFNetworkTask<REQ, RESP> *)>&& cb) :
		CommRequest(object, scheduler),
		callback(std::move(cb))
	{
		this->user_data = NULL;
		this->send_timeo = -1;
		this->receive_timeo = -1;
		this->keep_alive_timeo = 0;
		this->target = NULL;
		this->timeout_reason = TOR_NOT_TIMEOUT;
		this->state = WFT_STATE_UNDEFINED;
		this->error = 0;
	}
    {
        void *user_data;
        int send_timeo;
	    int receive_timeo;
	    int keep_alive_timeo;
	    REQ req;
	    RESP resp;
	    std::function<void (WFNetworkTask<REQ, RESP> *)> callback;
    }

5 class CommRequest : public SubTask, public CommSession                            CommRequest.h
    CommRequest(CommSchedObject *object, CommScheduler *scheduler)
	{
		this->scheduler = scheduler;
		this->object = object;
		this->wait_timeout = 0;
	}
    {
        int state;
	    int error;
        int wait_timeout;
        CommTarget *target;
	    int timeout_reason;
	    CommSchedObject *object;
	    CommScheduler *scheduler;
    }

6 class SubTask                                                                     SubTask.h
  	SubTask()
	{
		this->parent = NULL;
		this->entry = NULL;
		this->pointer = NULL;
	}
    {
        ParallelTask *parent;
	    SubTask **entry;
	    void *pointer;
    }
  class CommSession                                                                 Communicator.h
    CommSession() 
    { 
        this->passive = 0; 
    }
    {
        CommTarget *target;
	    CommConnection *conn;
	    CommMessageOut *out;
	    CommMessageIn *in;
	    long long seq;
        struct timespec begin_time;
	    int timeout;
	    int passive;
    }


=========================================================================================================
    class HttpRequest : public HttpMessage                                         HttpMessage.h
    HttpRequest() : HttpMessage(false) 
    { 

    }
    {

    }
    class HttpMessage : public ProtocolMessage                                     HttpMessage.h
    HttpMessage(bool is_resp) : parser(new http_parser_t)
	{
		http_parser_init(is_resp, this->parser);
		INIT_LIST_HEAD(&this->output_body);
		this->output_body_size = 0;
		this->cur_size = 0;
	}
    {
        http_parser_t *parser;
	    size_t cur_size;
        struct list_head output_body;
	    size_t output_body_size;
    }

    class ProtocolMessage : public CommMessageOut, public CommMessageIn            ProtocolMessage.h
    ProtocolMessage()
	{
		this->size_limit = (size_t)-1;
		this->attachment = NULL;
	}
    {
        size_t size_limit;
        Attachment *attachment;
    }
    class CommMessageOut                                                          Communicator.h

    class CommMessageIn : private poller_message_t                                Communicator.h
    {
        struct CommConnEntry *entry;
    }
    
    struct __poller_message                                                       poller.h
    {
        int (*append)(const void *, size_t *, poller_message_t *);
        char data[0];
    };

===========================================================================================================

class HttpResponse : public HttpMessage                                           HttpMessage.h
HttpMessage(true) 
{

}

===========================================================================================================
class ParsedURI
{
    
}
{
    char *scheme;
    char *userinfo;
    char *host;
    char *port;
    char *path;
    char *query;
    char *fragment;
    int state;
    int error;
}

==========================================================================================

class WaitGroup

WaitGroup(int n) : nleft(n)
{
    if (n <= 0)
    {
        this->nleft = -1;
        return;
    }
    auto *pr = new WFPromise<void>();
    this->task = WFTaskFactory::create_counter_task(1, __wait_group_callback);
    this->future = pr->get_future();
    this->task->user_data = pr;
    this->task->start();
}

{
    std::atomic<int> nleft;
    WFCounterTask *task;
    WFFuture<void> future;
}


===============================================================
class WFCounterTask : public WFGenericTask                        WFTask.h
WFCounterTask(unsigned int target_value,
            std::function<void (WFCounterTask *)>&& cb) :
            value(target_value + 1),
            callback(std::move(cb))
{

}

{
    std::atomic<unsigned int> value;
    std::function<void (WFCounterTask *)> callback;
}

class WFGenericTask : public SubTask                              WFTask.h
    WFGenericTask()
    {
        this->user_data = NULL;
        this->state = WFT_STATE_UNDEFINED;
        this->error = 0;
    }
{
    void *user_data;
    int state;
    int error;
}

class SubTask                                                    SubTask.h
SubTask()
{
    this->parent = NULL;
    this->entry = NULL;
    this->pointer = NULL;
}
{
    ParallelTask *parent;
    SubTask **entry;
    void *pointer;
}


class SeriesWork                                              Workflow.h
SeriesWork(SubTask *first, series_callback_t&& cb) :
	callback(std::move(cb))
{
    this->queue = new SubTask *[4];
    this->queue_size = 4;
    this->front = 0;
    this->back = 0;
    this->in_parallel = false;
    this->canceled = false;
    first->set_pointer(this);
    this->first = first;
    this->last = NULL;
    this->context = NULL;
}


{
    void *context;
    series_callback_t callback;
    SubTask *first;
    SubTask *last;
    SubTask **queue;
    int queue_size;
    int front;
    int back;
    bool in_parallel;
    bool canceled;
    std::mutex mutex;
}

class SeriesWork;
SeriesWork::SeriesWork(SubTask *first, series_callback_t&& cb) :
	callback(std::move(cb))
{
	this->queue = new SubTask *[4];
	this->queue_size = 4;
	this->front = 0;
	this->back = 0;
	this->in_parallel = false;
	this->canceled = false;
	first->set_pointer(this);
	this->first = first;
	this->last = NULL;
	this->context = NULL;
}


class ParallelWork : public ParallelTask



class ParallelTask : public SubTask
ParallelTask(SubTask **subtasks, size_t n)
{
	this->subtasks = subtasks;
	this->subtasks_nr = n;
}
{
    SubTask **subtasks;
    size_t subtasks_nr;
    size_t nleft;
    friend class SubTask;
}


