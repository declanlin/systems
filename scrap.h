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

