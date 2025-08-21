#ifndef CONFIG_HPP
#define CONFIG_HPP


#define MAX_CTR 144

#ifdef __linux__

    #define BUFFER MAX_CTR + 1

#elif defined(_WIN32) || defined(WIN32)
    
    #define BUFFER MAX_CTR + 3

#endif

#define MAX_CTR_SEND (BUFFER + 9)

#define IP_SERVER_HOST "127.0.0.1"
#define PORT_SERVER_HOST 2569

#define MAX_USERS 8



#endif
