// -*- C++ -*-
#include "Test_i.h"

Test_i::Test_i ()
  : orb_ ()
{
}

void
Test_i::invoke_me ( /* */)
{
  ACE_DEBUG ((LM_INFO,
              "(%P|%t) Test method invoked.\n"));
}

void
Test_i::shutdown ()
{
  ACE_DEBUG ((LM_INFO,
              "Server is shutting down.\n"));

  if (!CORBA::is_nil (this->orb_.in ()))
    this->orb_->shutdown (false);
}

void
Test_i::orb (CORBA::ORB_ptr orb)
{
  this->orb_ = CORBA::ORB::_duplicate (orb);
}
