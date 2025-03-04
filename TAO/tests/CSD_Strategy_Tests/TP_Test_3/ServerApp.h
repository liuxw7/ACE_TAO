#ifndef SERVERAPP_H
#define SERVERAPP_H

#include "TestAppBase.h"
#include "ServantList_T.h"
#include "ClientTask.h"
#include "Foo_B_i.h"
#include "Callback_i.h"
#include "tao/CSD_ThreadPool/CSD_TP_Strategy.h"
#include "ace/SString.h"


class ServerApp : public TestAppBase
{
  public:
    ServerApp();
    virtual ~ServerApp();


  protected:
    virtual int run_i(int argc, ACE_TCHAR* argv[]);


  private:
    // These are all called, in order, by the run_i() method.
    int  init(int argc, ACE_TCHAR* argv[]);
    void poa_setup();
    void csd_setup();
    void servant_setup();
    void collocated_setup();
    void poa_activate();
    void run_collocated_clients();
    void run_orb_event_loop();
    bool check_validity ();
    void cleanup();


    // Helper methods used by the methods above.
    int parse_args(int argc, ACE_TCHAR* argv[]);

    int set_arg(unsigned&   value,
                 const ACE_TCHAR* arg,
                 char        opt,
                 const char* name,
                 int         min = 0);

    void usage_statement();
    int  arg_dependency_checks();


    PortableServer::POA_ptr create_poa(CORBA::ORB_ptr orb,
                                       const char* poa_name);

    typedef ServantList<Foo_B_i> FooServantListType;
    typedef ServantList<Callback_i> CallbackServantListType;

    CORBA::ORB_var               orb_;
    PortableServer::POA_var      poa_;
    TAO::CSD::TP_Strategy_Handle tp_strategy_;

    PortableServer::POA_var      cb_poa_;
    TAO::CSD::TP_Strategy_Handle cb_tp_strategy_;

    FooServantListType foo_servants_;
    CallbackServantListType cb_servants_;

    ClientTask collocated_client_task_;

    ACE_TString exe_name_;

    ACE_TString ior_filename_prefix_;
    unsigned num_servants_;
    unsigned num_csd_threads_;
    unsigned num_orb_threads_;
    unsigned num_remote_clients_;
    unsigned num_collocated_clients_;
    unsigned collocated_client_kind_;
};

#endif
