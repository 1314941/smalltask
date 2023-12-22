package com.qst.dms.net;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import com.qst.dms.entity.MatchedLogRec;
import com.qst.dms.entity.MatchedTransport;
import com.qst.dms.service.LogRecService;
import com.qst.dms.service.TransportService;

//服务器应用程序，接收客户端发送来的数据保存到数据库中
public class DmsNetServer {
	public DmsNetServer() {
		// 通过使用不同的端口接收不同数据，6666端口是日志，6668端口是物流
		// 开启监听6666端口的线程，接收日志数据
		AcceptLogThread log = new AcceptLogThread(6666);
		log.start();
		// 开启监听6668端口的线程，接收物流数据
		AcceptTransThread tran = new AcceptTransThread(6668);
		tran.start();
		System.out.println("网络服务器已开启...");
	}

	private class AcceptLogThread extends Thread {
		private ServerSocket serverSocket;
		private Socket socket;
		// 是否停止进程
		private LogRecService logRecService;
		private ObjectInputStream ois;

		public AcceptLogThread(int port) {
			logRecService = new LogRecService();
			try {
				serverSocket = new ServerSocket(port);
				if (serverSocket == null) {
					System.out.println("serversocket==null");
				}
			} catch (IOException e) {
				e.printStackTrace();
				// TODO: handle exception
			}
		}

		// 重写run()方法，将日志数据保存到数据库
		@Override
		public void run() {
			while (this.isAlive()) {
				try {
					// 接收客户端发送过来的套接字
					socket = serverSocket.accept();
					if (socket != null) {
						ois = new ObjectInputStream(socket.getInputStream());
						// 反序列化，得到匹配日志列表
						ArrayList<MatchedLogRec> matchedLogs = (ArrayList<MatchedLogRec>) ois.readObject();
						// 将客户端发送来的匹配日志信息保存到数据库
						logRecService.saveMatchLogToDB(matchedLogs);
					}
				} catch (Exception e) {
					e.printStackTrace();
					break;
					// TODO: handle exception
				}
			}
			try {
				ois.close();
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
				// TODO: handle exception
			}
			// 服务端接收到一个客户端请求的时候，就与客户端通信，通信结束后断开连接，才会接收下一个客户端请求。
			// 如果同时多个客户端连接，这些客户端请求就必须在队列中排队，等待服务端一个一个的请求的处理。
			// 服务端是无法同时处理多个请求的，服务端是无法同时和多个客户端通信的
			// 断开连接
		}
	}

	private class AcceptTransThread extends Thread {
		private ServerSocket serverSocket;
		private Socket socket;
		// 判断进程是否停止
		private TransportService transportService;
		private ObjectInputStream ois;

		public AcceptTransThread(int port) {
			transportService = new TransportService();
			try {
				serverSocket = new ServerSocket(port);
				if (serverSocket == null) {
					System.out.println("serversocket==null");
				}
			} catch (IOException e) {
				e.printStackTrace();
				// TODO: handle exception
			}
		}

		// 重写run()方法，将日志数据保存到数据库
		// run()方法运行完，进程就停止了
		@Override
		public void run() {
			while (this.isAlive()) {
				try {
					// 接收客户端发送过来的套接字
					socket = serverSocket.accept();
					if (socket != null) {
						ois = new ObjectInputStream(socket.getInputStream());
						// 反序列化，得到匹配日志列表
						ArrayList<MatchedTransport> matchedTrans = (ArrayList<MatchedTransport>) ois.readObject();
						// 将客户端发送来的匹配日志信息保存到数据库
						transportService.saveMatchTransportToDB(matchedTrans);
					}
				} catch (Exception e) {
					e.printStackTrace();
					break;
					// TODO: handle exception
				}
			}
			try {
				ois.close();
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
				// TODO: handle exception
			}

		}

	}

	// 主程序
	public static void main(String[] args) {
		new DmsNetServer();
	}

}
