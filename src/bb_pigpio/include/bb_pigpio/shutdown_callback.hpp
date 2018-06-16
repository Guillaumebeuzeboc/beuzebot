#ifndef SHUTDOWN_CALLBACK_HPP
#define SHUTDOWN_CALLBACK_HPP


#include <signal.h>
#include <ros/xmlrpc_manager.h>

// Signal-safe flag for whether shutdown is requested
sig_atomic_t volatile g_request_shutdown = 0;

// Replacement SIGINT handler
void mySigIntHandler(int sig)
{
  g_request_shutdown = 1;
}

// Replacement "shutdown" XMLRPC callback
void shutdownCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result) {
  int num_params = 0;
  if (params.getType() == XmlRpc::XmlRpcValue::TypeArray) {
    num_params = params.size();
  }
  if (num_params > 1) {
    std::string reason = params[1];
    ROS_WARN("Shutdown request received. Reason: [%s]", reason.c_str());
    g_request_shutdown = 1; // Set flag
  }

  result = ros::xmlrpc::responseInt(1, "", 0);
}

#endif // SHUTDOWN_CALLBACK_HPP
