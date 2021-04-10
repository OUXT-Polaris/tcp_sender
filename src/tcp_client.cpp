// Copyright (c) 2021 OUXT Polaris
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <tcp_sender/tcp_client.hpp>

#include <string>

namespace tcp_sender
{
TcpClient::TcpClient(
  boost::asio::io_service & io_service, const rclcpp::Logger & logger)
: io_service_(io_service),
  socket_(io_service_),
  logger_(logger)
{
}

void TcpClient::connect(const std::string & address, const int & port)
{
  socket_.connect(
    boost::asio::ip::tcp::endpoint(
      boost::asio::ip::address::from_string(address),
      port));
}

void TcpClient::send(const std::string & message)
{
  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);
}
}  // namespace tcp_sender
