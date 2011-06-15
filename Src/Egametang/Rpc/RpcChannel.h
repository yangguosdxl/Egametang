#ifndef RPC_RPC_CHANNEL_H
#define RPC_RPC_CHANNEL_H

#include <google/protobuf/service.h>
#include <boost/unordered_map.hpp>
#include <boost/asio.hpp>
#include "Base/Typedef.h"
#include "Rpc/RpcTypedef.h"
#include "Rpc/RpcCommunicator.h"

namespace Egametang {

class RpcHandler;

class RpcChannel:
		public google::protobuf::RpcChannel,
		public RPCCommunicator
{
private:
	typedef boost::unordered_map<int32, RpcHandlerPtr> RpcCallbackMap;

	int32 id_;
	RpcCallbackMap handlers_;
	boost::asio::io_service& io_service_;

	void AsyncConnectHandler(const boost::system::error_code& err);

	// recieve response
	virtual void OnRecvMessage(StringPtr ss, const boost::system::error_code& err);

	// send request
	virtual void OnSendMessage(int32 id, RpcHandlerPtr handler,
			const boost::system::error_code& err);

public:
	RpcChannel(boost::asio::io_service& service, std::string& host, int port);
	~RpcChannel();
	virtual void CallMethod(
			const google::protobuf::MethodDescriptor* method,
			google::protobuf::RpcController* controller,
			const google::protobuf::Message* request,
			google::protobuf::Message* response,
			google::protobuf::Closure* done);
};

} // namespace Egametang

#endif // RPC_RPC_CHANNEL_H