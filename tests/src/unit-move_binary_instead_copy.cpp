//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++ (supporting code)
// |  |  |__   |  |  | | | |  version 3.11.2
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// Copyright (c) 2013-2022 Niels Lohmann <http://nlohmann.me>.
// SPDX-FileCopyrightText: 2013-2022 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#include "doctest_compatibility.h"

#include <nlohmann/json.hpp>

class Buffer : public std::vector<char>
{
  public:
    using MyBase = std::vector<char>;
    using MyBase::MyBase;
    Buffer() = default;
    ~Buffer() = default;

    Buffer(Buffer&& other) noexcept
      : MyBase(std::move(other))
    {}

    Buffer& operator=(Buffer&& other) noexcept
    {
        MyBase::operator=(std::move(other));
        return *this;
    }

    // Break if copy is used
    Buffer(const Buffer& other)
    {
        REQUIRE(0);
    }

    Buffer& operator=(const Buffer& other)
    {
        REQUIRE(0);
        return *this; /* prevent compiler warning */
    }
};

using json = nlohmann::basic_json<
    std::map,
    std::vector,
    std::string,
    bool,
    std::int64_t,
    std::uint64_t,
    double,
    std::allocator,
    nlohmann::adl_serializer,
    Buffer /* binary_t */>;

TEST_CASE("use move instead of copying the binary value")
{
    json testJson;
    testJson["buf"] = json::binary_t(Buffer(100, '1'));
}
