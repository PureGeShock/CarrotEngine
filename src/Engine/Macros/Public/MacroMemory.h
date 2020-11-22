#pragma once

#include <memory>

#define PTR( cls )	using cls##Ptr = std::shared_ptr< class cls >; \
                    using cls##ConstPtr = std::shared_ptr< class cls const >; \
                    using cls##WPtr = std::weak_ptr< class cls >; \
                    using cls##ConstWPtr = std::weak_ptr< class cls const >;
