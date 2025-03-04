#include "Receiver_i.h"

Receiver_i::Receiver_i (CORBA::ORB_ptr orb,
                        Test::Sender_ptr sender,
                        CORBA::ULong iter)
  : no_calls_ (0),
    orb_ (CORBA::ORB::_duplicate (orb)),
    sender_ (Test::Sender::_duplicate (sender)),
    iteration_ (iter)
{
}

Receiver_i::~Receiver_i ()
{
}

CORBA::Long
Receiver_i::receive_call ()
{
  ACE_DEBUG ((LM_DEBUG,
              "(%P|%t)  Doing a ping...\n"));

  this->sender_->ping ();

  return this->no_calls_++;
}

CORBA::Long
Receiver_i::get_call_count ( /**/)
{
  return this->iteration_;
}

void
Receiver_i::shutdown ()
{
  ACE_DEBUG ((LM_DEBUG,
              "(%P|%t) About to invoke shutdown...\n"));
  this->orb_->shutdown (false);
}
