#include "./QueryTable.h"

#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>

#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class SharedonServer
{
  enum QueryType { ADD, DEL, QUERY };
      
public:
  SharedonServer(EventLoop          *loop, 
                 const InetAddress&  listenAddr,
                 int                 numThreads,
                 int                 numAddr)
    : _server    (loop, listenAddr, "SharedonServer"),
      _numThreads(numThreads),
      _startTime (Timestamp::now()),
      _numAddr   (numAddr)
  {
    _server.setConnectionCallback(
        boost::bind(&SharedonServer::onConnection, this, _1));
    _server.setMessageCallback(
        boost::bind(&SharedonServer::onMessage, this, _1, _2, _3));
  }

  void start()
  {
    LOG_INFO << "starting " << _numThreads << " threads.";
    _threadPool.start(_numThreads);
    _server.start();
  }

private:
     
  void onConnection(const TcpConnectionPtr& conn);
  void onMessage   (const TcpConnectionPtr& conn, Buffer* buf, Timestamp);

  bool processRequest(const TcpConnectionPtr& conn, const std::string& request);

  static void query(const TcpConnectionPtr&   conn,
              QueryType                 t, 
              QueryTable&               qTable, 
              const std::string         fileName, 
              const std::string&        address, 
              int                       num);
  
  static void parseRequest(const std::string& s,
                           std::string&       fileName,
                           std::string&       address,
                           QueryType&         t);
 
  static void resultToString(std::vector<std::string>& result, std::string& str);

private:
  TcpServer  _server;
  ThreadPool _threadPool;
  int        _numThreads;
  Timestamp  _startTime;
  int        _numAddr;
};


