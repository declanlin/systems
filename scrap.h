// #pragma once is a preprocessor directive that
// ensures a header file is processed only once per
// translation unit in a single compilation. 

#pragma once


// <cstdint> is a C++ standard library header that provides
// integer types with more precise control over exact integer
// widths, integer width guarantees, and signedness.

#include <cstdint>


// With an unscoped enumeration, the enumerator identifiers "Bid"
// and "Ask" are introducted into the scope surrounding "Side",
// potentially causing naming conflicts with other identifiers
// in the same scope.

// Unscoped enumerations also allow their enumerator values to be
// implicitly converted to integral types, reducing type safety.

    // Example 1:

    /*
    
        enum Side { Bid, Ask };
        void setVolume(
            std::uint64_t orderId,
            std::uint32_t volume
        ) {
            // ...
        }
          
        // The below function call does not cause any compilation
        // error since Ask is implicitly converted to its integral
        // value. Semantically, it makes no sense to be passing
        // an order side to a parameter for the order volume.

        setVolume(1, Ask);
         
    */

    // Example 2:

    /*

        enum Side { Bid, Ask };
        Side side{Ask};

        if (side == 1) {
            // ...
        }

        // The code above compiles, but the program logic is
        // now coupled to the underlying numeric representation of
        // Ask as opposed to its semantic meaning as an enumerator.
    
        if (side == Ask) {
            // ...
        }

    */

// enum Side { Bid, Ask };

// A scoped enumeration keeps "Bid" and "Ask" within the scope of
// "Side", requiring them to be referenced as Side::Bid and
// Side::Ask.

// Scoped enumerations also prevent implicit conversion to
// integral types. Type conversions for scoped enumerators
// require an explicit cast to signal to the compiler that
// you intend to cross a type boundary, e.g., by using
// static_cast<std::uint32_t>(Side::Ask).

enum class Side : std::uint8_t { Bid, Ask };

// Prior to C++11, type aliases were created using:

// typedef std::uint64_t OrderId;

// With the introduction of the "using" keyword in C++11, type aliases
// can be created as follows:

using OrderId = std::uint64_t;
using Price = std::int64_t;
using Volume = std::uint32_t;

// Useful thoughts:

/*

The engine's job is almost stupidly mechanical:
    Do any currently compatible intentions exist?

The matching engine does not determine the fundamental value of the asset.
Those prices exist because actual market participants have submitted orders saying:
    Buyer A:  I'll pay up to $99.
    Seller B: I won't sell for less than $101.

If you're aggressive, your limit orders will probably get filled faster.
However, your limit is permission to the matching engine to keep consuming liquidity up
to that price.

*/
