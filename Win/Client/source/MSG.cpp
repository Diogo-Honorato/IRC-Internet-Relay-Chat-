#include "../include/MSG.hpp"


int initClient(Client *c){
	
	socklen_t size = sizeof(c->server_target);
	
	c->client_fd = socket(DOMAIN, SOCK_STREAM,0);
	
	c->server_target.sin_port = htons(PORT_SERVER_LOCAL);
	c->server_target.sin_family = DOMAIN;
	c->server_target.sin_addr.s_addr = inet_addr(IP_SERVER_LOCAL);
	
	int status = -1;
	
	std::cout << "TRYING CONNECTION\n";
	
	while(status != 0){
		status = connect(c->client_fd,(struct sockaddr*)&c->server_target,size);
	}
	
	c->run = 1;

	return 0;
}

int inputMSG(Client *c){
	
	std::cout << "Send Message\n";
	std::vector<char> buffer(MAX_CTR);
	std::string msg;
	
	while(c->run){
	
		std::cout << ">> ";

		std::getline(std::cin,msg);
		
		if(msg.size() > 0){
		
			if(msg.size() >= MAX_CTR){
			
				msg.resize(MAX_CTR);
				msg[MAX_CTR-1] = '\0';
			}
			

			strcpy(buffer.data(),msg.c_str());

			if(msg == END){

				send(c->client_fd,buffer.data(),buffer.size(),MSG_NOSIGNAL);
				std::cout << "CLOSING...\n";
				sleep(1);
				break;
			}
		
			if(send(c->client_fd,buffer.data(),buffer.size(),MSG_NOSIGNAL) == -1){
					
				return -1;
			}	
		}
		
		buffer.clear();
		buffer.resize(MAX_CTR);
		msg.clear();
		msg.resize(MAX_CTR);
	}	

	return 0;
}



int main(){

	Client c;

	if(initClient(&c) == -1){
	
		std::cerr << "CONNECT FAILED\n";
		close(c.client_fd);
		exit(EXIT_FAILURE);
	}

	std::cout << "MSG CONNECTED\n\n";
	
	
	if(inputMSG(&c) == -1){
		
		std::cerr << "SERVER LOCAL OFFLINE\n";
		close(c.client_fd);
		exit(EXIT_FAILURE);
	}
	
	close(c.client_fd);
	std::cout << "\nMSG CLOSED\n";

	return 0;
}	
