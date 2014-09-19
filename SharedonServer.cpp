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
  void onConnection(const TcpConnectionPtr& conn)
  {
    LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
  }

  void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp)
  {
    LOG_DEBUG << conn->name();
    size_t len = buf->readableBytes();
    if (len < 100) {
      const char* crlf = buf->findCRLF();
      if (crlf) {              
        std::string request(buf->peek(), crlf); 
        if (!processRequest(conn, request))
        {
          conn->send("Bad Request!\r\n");
          conn->shutdown();
          return;
        }
      }
      return;
    }
    conn->send("Too long request!\r\n");
    conn->shutdown();
  }

  bool processRequest(const TcpConnectionPtr& conn, const std::string& request)
  {
    std::string fileName;
    std::string address;
    QueryType   qType;
    bool        goodRequest = true;

    if (parseRequest(request, fileName, address, qType)) {
      _threadPool.run(boost::bind(&query, conn, qType, 
                                  queryTable, fileName, address, _numAddr));
    } else {
      goodRequest = false;
    }
    return goodRequest;
  }

  static void query(const TcpConnectionPtr&   conn,
              QueryType                 t, 
              QueryTable&               qTable, 
              const std::string         fileName, 
              const std::string&        address, 
              int                       num)
  {
    std::vector<std::string> result
    LOG_DEBUG << conn->name();
    switch (t) {
      case ADD:   _qTable.addToFile(fileName, address);
                  break;
                  
      case DEL:   _qTable.deleteFromFile(fileName, address);
                  break;
                  
      case QUERY: _qTable.queryFile(fileName, address, num, result);
                  std::string resultStr;
                  resultToString(result, resultStr);
                  conn->send(resultStr+"\r\n");
    }
    conn->shutdown();
  }
  
  static bool parseRequest(const std::string& s,
                           std::string&       fileName,
                           std::string&       address,
                           QueryType&         t);
  {
                             
  }
  
  static void resultToString(std::vector<std::string>& result, std::string& str)
  {
    if (result.empty()) {
      str += "No matched file!";
    } else {
      str += "File addresses: ";
      for (std::vector<std::string>::iterator it; it != result.it(); it++) { 
        str += (result + "; ");
      }
    }    
  }

private:
  TcpServer  _server;
  ThreadPool _threadPool;
  int        _numThreads;
  Timestamp  _startTime;
  int        _numAddr;
  QureyTable _qTable;
};


int main(int argc, char* argv[])
{
  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  int numThreads = 0;
  int numAddr    = 5;
  if (argc > 2) {
    numThreads = atoi(argv[1]);
    numAddr    = atoi(argv[2]);
  }
  EventLoop      loop;
  InetAddress    listenAddr(10001);
  SharedonServer server(&loop, listenAddr, numThreads, numAddr);

  server.start();

  loop.loop();
}


