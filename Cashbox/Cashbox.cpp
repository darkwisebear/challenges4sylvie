#include <iostream>
#include <iomanip>
#include <cassert>

#include "Solution.h"

// In diesem Beispiel soll eine Kasse simuliert werden. Mit "add_position soll ein Eintrag hinzugefügt werden, also so
// als ob der Kassierer was über den Scanner zieht.
// Im Beispiel gibt es zwei Arten von Einträgen: Ein Eintrag für Stückware ("PerPiecePosition") und einer für
// abgewogene Ware ("WeightPosition").
// "num_positions" soll die Anzahl der aktuellen Einträge wiedergeben. "get_position" soll den Eintrag an einer
// bestimmten Position zurückgeben.
// Jede Position hat folgende Methoden:
// "get_amount" gibt einen String zurück der beschreibt, wieviel von der Ware gekauft wurde.
// "to_string" gibt eine Beschreibung der Ware zurück.
// "total_price" gibt den Gesamtpreis des Postens zurück.
// Die Kasse selbst hat ebenfalls eine Methode "total_price" die die Endsumme zurückgibt.

int main() {
    Cashbox c;
    // add five Milk for 1.09 each
    c.add_position(new PerPiecePosition("Milk", 1.09, 5));
    // add 85.5g of Stinky Cheese that costs 2.99 per 100g
    c.add_position(new WeightPosition("Stinky Cheese", 2.99, 100.0, "g", 85.5));

    // Print final bill
    for (size_t i = 0; i < c.num_positions(); ++i) {
        const Position& pos = c.get_position(i);
        std::cout << std::setw(12) << pos.get_amount() << ' '
            << std::setw(40) << pos.to_string() << ' ' << pos.total_price() << std::endl;
    }

    const double total = c.total_price();
    std::cout << "Total price: " << total << std::endl;

    // Check whether the total price is what we would expect :)
    assert(std::abs(total - 8.01) < 0.005);
}
