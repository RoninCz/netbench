#include <iostream>
#include <string>
#include "CLI11.hpp"
struct ServerConfig{
	int port = 8080;
	std::string proto = "tcp";
	std::string backend = "blocking";
};

struct ClientConfig{
	int port = 9000;
	int connections = 1;
	int requests = 10000;
	int payload = 64;
	std::string proto = "tcp";
	std::string target = "127.0.0.1";
};


int main(int argc, char** argv){
	CLI::App app("Netbench - 高性能网络测试框架");
	
	// 全局参数定义
	std::string config_file;
	app.add_option("-c,--config", config_file, "指定配置文件路径");

	ServerConfig server_cfg;
	ClientConfig client_cfg;

	// 定义子命令server
	CLI::App* server = app.add_subcommand("server", "启动服务端相关命令");
	server->add_option("-p,--proto", server_cfg.proto, "协议，tcp/udp")->default_val("tcp");
	server->add_option("-b,--backend", server_cfg.backend, "模式，阻塞或非阻塞，blocking")->default_val("blocking");
	server->add_option("-P,--port", server_cfg.port, "服务端监听端口")->default_val("8080");

	// 定义子命令client
	CLI::App* client = app.add_subcommand("client", "启动客户端相关命令");
	client->add_option("-p,--proto", client_cfg.proto, "协议，tcp/udp")->default_val("tcp");
	client->add_option("-t,--target", client_cfg.target, "目标ip地址")->required();
	client->add_option("-P,--port", client_cfg.port, "客户端监听端口")->default_val("9000");
	client->add_option("-c,--connections", client_cfg.connections, "连接数量")->default_val("1");
	client->add_option("-r,--requests", client_cfg.requests, "请求数量")->default_val("10000");
	client->add_option("-l,--payload", client_cfg.payload, "负载大小")->default_val("64");
	
	CLI11_PARSE(app, argc, argv);

	// 命令行匹配
	if (*server){
		std::cout << "Server port" << server_cfg.port << std::endl;
	}else if (*client){
		std::cout << "Client port" << client_cfg.port << std::endl;
	}

	return 0;
}
