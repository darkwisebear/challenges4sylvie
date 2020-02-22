#ifndef CASHBOX_H
#define CASHBOX_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

class Position {
protected:
    std::string name;

    explicit Position(std::string name) : name(name) {}

public:
    virtual std::string to_string() const = 0;
    virtual std::string get_amount() const = 0;
    virtual double total_price() const = 0;
    const std::string& get_name() const { return name; }
};

class PerPiecePosition : public Position {
private:
    double price_per_piece;
    unsigned int num_pieces;

public:
    PerPiecePosition(std::string name, double price, unsigned int num) :
        Position(name),
        price_per_piece(price),
        num_pieces(num) {}

    std::string to_string() const {
        std::stringstream ss;
        ss << name << " (" << price_per_piece << " per piece)";
        return ss.str();
    }

    std::string get_amount() const {
        std::stringstream ss;
        ss << num_pieces;
        return ss.str();
    }

    double total_price() const {
        return price_per_piece * num_pieces;
    }
};

class WeightPosition : public Position {
private:
    double ref_price;
    double ref_weight;
    double weight;
    std::string unit;

public:
    WeightPosition(std::string name, double ref_price, double ref_weight, std::string unit, double weight) :
        Position(name),
        ref_price(ref_price),
        ref_weight(ref_weight),
        weight(weight),
        unit(unit) {}

    std::string to_string() const {
        std::stringstream ss;
        ss << name << " (" << ref_price << '/' << ref_weight << unit << ')';
        return ss.str();
    }

    std::string get_amount() const {
        std::stringstream ss;
        ss << weight << unit;
        return ss.str();
    }

    double total_price() const {
        return weight * ref_price / ref_weight;
    }
};

class Cashbox {
private:
    std::vector<Position*> positions;

public:
    Cashbox() = default;
    ~Cashbox() {
        std::for_each(positions.begin(), positions.end(), [](auto& item) { delete item; });
    }

    void add_position(Position* pos) {
        positions.push_back(pos);
    }

    size_t num_positions() const {
        return positions.size();
    }

    const Position& get_position(size_t pos) const {
        return *positions[pos];
    }

    double total_price() const {
        return std::accumulate(positions.begin(), positions.end(), 0.0,
            [](double total, const Position* const p) { return total + p->total_price(); });
    }
};

#endif // CASHBOX_H
