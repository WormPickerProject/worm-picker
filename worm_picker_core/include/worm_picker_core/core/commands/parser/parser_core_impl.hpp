// parser_core_impl.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

namespace worm_picker { 
namespace parser {

//=======================================
// Template Parser Implementations
//=======================================

// Match a single character satisfying a predicate
template <typename Pred>
Parser<char> satisfy(Pred&& predicate, const std::string& description) 
{
    return [pred = std::forward<Pred>(predicate), description](ParserInput input) -> ParserResult<char> {
        if (input.atEnd()) {
            std::ostringstream oss;
            oss << "At " << input.positionInfo() << ": Unexpected end of input, expected " 
                << description;
            return ParserResult<char>::error(oss.str());
        }
        
        char c = input.current();
        if (pred(c)) {
            return ParserResult<char>::success({c, input.advance()});
        } else {
            std::ostringstream oss;
            oss << "At " << input.positionInfo() << ": Unexpected character '" << c 
                << "', expected " << description;
            return ParserResult<char>::error(oss.str());
        }
    };
}

template <typename T, typename U, typename Combiner>
Parser<typename std::invoke_result<Combiner, T, U>::type> 
combine(Parser<T> first, Parser<U> second, Combiner combiner) 
{
    using R = typename std::invoke_result<Combiner, T, U>::type;
    
    return [first, second, combiner](ParserInput input) -> ParserResult<R> {
        auto firstResult = first(input);
        if (!firstResult.isSuccess()) {
            return ParserResult<R>::error(firstResult.error());
        }
        auto [firstValue, firstRest] = firstResult.value();
        
        auto secondResult = second(firstRest);
        if (!secondResult.isSuccess()) {
            return ParserResult<R>::error(secondResult.error());
        }
        auto [secondValue, secondRest] = secondResult.value();
        
        return ParserResult<R>::success({
            combiner(firstValue, secondValue), 
            secondRest
        });
    };
}

// Try the first parser, and if it fails, try the second parser
template <typename T>
Parser<T> orElse(Parser<T> first, Parser<T> second) 
{
    return [first, second](ParserInput input) -> ParserResult<T> {
        auto result = first(input);
        if (result.isSuccess()) {
            return result;
        }
        return second(input);
    };
}

// Try multiple parsers in order until one succeeds
template <typename T>
Parser<T> choice(const std::vector<Parser<T>>& parsers) 
{
    return [parsers](ParserInput input) -> ParserResult<T> {
        std::vector<std::string> errors;
        errors.reserve(parsers.size());
        
        for (const auto& parser : parsers) {
            auto result = parser(input);
            if (result.isSuccess()) {
                return result;
            }
            errors.push_back(result.error());
        }
        
        std::ostringstream oss;
        oss << "At " << input.positionInfo() << ": None of the parsers succeeded: ";
        
        for (size_t i = 0; i < errors.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << errors[i];
        }
        
        return ParserResult<T>::error(oss.str());
    };
}

// Delimiter-separated list of items
template <typename T, typename U>
Parser<std::vector<T>> sepBy(Parser<T> parser, Parser<U> separator) 
{
    return [parser, separator](ParserInput input) -> ParserResult<std::vector<T>> {
        std::vector<T> results;
        
        // Try to parse the first item
        auto firstResult = parser(input);
        if (!firstResult.isSuccess()) {
            // Empty list is OK
            return ParserResult<std::vector<T>>::success({results, input});
        }
        
        auto [firstValue, rest] = firstResult.value();
        results.push_back(std::move(firstValue));
        ParserInput currentInput = rest;
        
        while (true) {
            auto sepResult = separator(currentInput);
            if (!sepResult.isSuccess()) {
                break;
            }
            
            auto [sepValue, afterSep] = sepResult.value();
            
            auto itemResult = parser(afterSep);
            if (!itemResult.isSuccess()) {
                break;
            }
            
            auto [itemValue, afterItem] = itemResult.value();
            results.push_back(std::move(itemValue));
            currentInput = afterItem;
        }
        
        return ParserResult<std::vector<T>>::success({results, currentInput});
    };
}

} // namespace parser
} // namespace worm_picker