#include <catch.hpp>
#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <string>

TEST_CASE("try to get data about a user's Disk with wrong token", "[client][info]") {
    // Given
    std::string wrong_token = "wrong_token";
    ydclient client{ wrong_token };
    // When
    auto data = client.info();
    // Then
    REQUIRE(data["error"].get<std::string>() == "UnauthorizedError");
    REQUIRE(data["description"].get<std::string>() == "Unauthorized");
    REQUIRE(data["message"].get<std::string>() == "Не авторизован.");
}

TEST_CASE("try to get data about a user's Disk with right token", "[client][info]") {
    // Given
    std::string right_token = "AQAAAAATPnx3AAQXOJS1w4zmPUdrsJNR1FATxEM";
    ydclient client{ right_token };
    // When
    auto data = client.info();
    // Then
    REQUIRE(data.find("is_paid") != data.end());
    REQUIRE(data.find("revision") != data.end());
    REQUIRE(data.find("system_folders") != data.end());
    REQUIRE(data.find("total_space") != data.end());
    REQUIRE(data.find("trash_size") != data.end());
    REQUIRE(data.find("used_space") != data.end());
}

TEST_CASE("verify that trash_size, total_space, used_space are numbers", "[client][info]") {
    // Given
    std::string right_token = "AQAAAAATPnx3AAQXOJS1w4zmPUdrsJNR1FATxEM";
    ydclient client{ right_token };
    // When
    auto data = client.info();
    // Then
    REQUIRE(data.find("total_space") != data.end());
    REQUIRE(data.find("trash_size") != data.end());
    REQUIRE(data.find("used_space") != data.end());
    REQUIRE(data["total_space"].is_number());
    REQUIRE(data["trash_size"].is_number());
    REQUIRE(data["used_space"].is_number());
}
