#include <optional>
#include <vector>
#include <uvw.hpp>
#include <memory>

class Server
{
public:
	Server(uvw::Loop& loop);
	~Server() = default;
	void Send(uint8_t* data, uint8_t size);

private:
	std::vector<std::shared_ptr<uvw::TCPHandle>> listClients;
};