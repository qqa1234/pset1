#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

/**
 * This struct describes a term in a polynomial with a link to
 * the next term. Note that the head of the polynomial shall be
 * the term with the highest exponent and each term will point
 * to a term with a lower exponent. 
 */
struct Node
{
    int coeff;
    int exp;
    Node* next;

    Node(int c, int e)
    {
        coeff = c;
        exp = e;
        next = nullptr;
    }
};

// Evaluate polynomial given by head for the given x
double eval(Node* head, double x)
{
    double temp = 0;
    while (head)
    {
        temp += head -> coeff * std::exp(x, head -> exp);

        head = head -> next;
    }

    return temp;
}

// Adds the two polynomials given by head1 and head2 and returns
// the head of the resulting polynomial
Node* addPolynomials(Node* head1, Node* head2)
{
    while (head1)
    {
        
    }
}

int main()
{
    // Example test - write at least 5 unique cases of your own!

    // p1 represents 3x^2 - 5x + 7
    Node* p1 = new Node(3, 2);
    p1->next = new Node(-5, 1);
    p1->next->next = new Node(7, 0);

    // p2 represents 6x - 3
    Node* p2 = new Node(6, 1);
    p2->next = new Node(-3, 0);

    // recall that floating point arithmetic can be finicky! 
    double epsilon = .00001;
    assert(abs(eval(p1, 2.0) - 9.0) < epsilon);

    // p3 should be 3x^2 + x + 4
    Node* p3 = addPolynomials(p1, p2);
    assert(p3->coeff == 3 && p3->exp == 2);
    assert(p3->next->coeff == 1 && p3->next->exp == 1);
    assert(p3->next->next->coeff == 4 && p3->next->next->exp == 0);

    // can we do this better?
    delete p1->next->next;
    delete p1->next;
    delete p1;
    delete p2->next;
    delete p2;
    delete p3->next->next;
    delete p3->next;
    delete p3;
}

