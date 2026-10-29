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
        temp += head -> coeff * std::pow(x, head -> exp);

        head = head -> next;
    }

    return temp;
}

// Adds the two polynomials given by head1 and head2 and returns
// the head of the resulting polynomial

Node* addPolynomials(Node* head1, Node* head2)
{
    Node* result = nullptr;
    Node* tail = nullptr;

    while (head1 || head2 )
    {
        int coeff;
        int exp;

        if (head2 == nullptr || (head1 != nullptr && head1->exp > head2->exp)   )
        {
            coeff = head1->coeff;
            exp = head1->exp;
            head1 = head1->next;
        }


        else if (head1 == nullptr || head2->exp > head1->exp)
        {
            coeff = head2->coeff;
            exp = head2->exp;
            head2 = head2->next;
        }


        else
        {
            coeff = head1->coeff + head2->coeff;
            exp = head1->exp;

            head1 = head1->next;
            head2 = head2->next;
        }

        if (coeff != 0)
        {
            Node* newNode = new Node(coeff, exp);

            if (result == nullptr)
            {
                result = newNode;
                tail = newNode;
            }

            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    return result;
}

void deletePolynomial(Node* head)
{

    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
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

    // my code >
    // Test1
    assert(std::abs(eval(p1, 0.0) - 7.0) < epsilon);

    // Test2
    assert(std::abs(eval(p1, -1.0) - 15.0) < epsilon);

    // Test3
    Node* p4 = addPolynomials(p1, nullptr);
    assert(p4 != nullptr);
    assert(p4->coeff == 3 && p4->exp == 2);
    assert(p4->next->coeff == -5);

    // Test4
    Node* a = new Node(2, 3);
    Node* b = new Node(-2, 3);

    Node* p5 = addPolynomials(a, b);
    assert(p5 == nullptr);

    // Test5
    Node* c = new Node(4, 4);
    c->next = new Node(2, 0);
    Node* d = new Node(3, 2);
    Node* p6 = addPolynomials(c, d);

    assert(p6->coeff == 4 && p6->exp == 4);
    assert(p6->next->coeff == 3 && p6->next->exp == 2);
    assert(p6->next->next->coeff == 2 && p6->next->next->exp == 0);
    assert(p6->next->next->next == nullptr);

    deletePolynomial(p4);
    deletePolynomial(a);
    deletePolynomial(b);
    deletePolynomial(p5);
    deletePolynomial(c);
    deletePolynomial(d);
    deletePolynomial(p6);
    // my code <

    // can we do this better?
    /*
    delete p1->next->next;
    delete p1->next;
    delete p1;
    delete p2->next;
    delete p2;
    delete p3->next->next;
    delete p3->next;
    delete p3;
    */

    deletePolynomial(p1);
    deletePolynomial(p2);
    deletePolynomial(p3);
}

