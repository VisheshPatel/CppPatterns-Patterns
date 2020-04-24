// Visitor Design Pattern in ModernCpp

struct Document {
    virtual void add_to_list(const string &line) = 0;
};
struct Markdown : Document {
    void add_to_list(const string &line) { m_content.push_back(line); }
    string          m_start = "* ";
    list<string>    m_content;
};
struct HTML : Document {
    void add_to_list(const string &line) { m_content.push_back(line); }
    string          m_start = "<li>";
    string          m_end = "</li>";
    list<string>    m_content;
};

/* ------------------------------------ Visitor ------------------------------------- */
struct DocumentPrinter {
    void operator()(Markdown &md) {
        for (auto &&item : md.m_content)
            cout << md.m_start << item << endl;
    }
    void operator()(HTML &hd){
        cout << "<ul>" << endl;
        for (auto &&item : hd.m_content)
            cout << "\t" << hd.m_start << item << hd.m_end << endl;
        cout << "</ul>" << endl;
    }
};
/* ---------------------------------------------------------------------------------- */

using document = std::variant<Markdown, HTML>;

int main() {
    HTML hd;
    hd.add_to_list("This is line");
    document d = hd;
    DocumentPrinter dp;
    std::visit(dp, d);
    return EXIT_SUCCESS;
}

// To define a new operation on a group of similar kind of objects or hierarchy
// without modifying the heirarchy. 
//
// I would not discuss the application of visitor, you can get it here
// in [classical visitor](http://www.vishalchovatiya.com/double-dispatch-visitor-design-pattern-in-modern-cpp/)
//
// So, let's directly jumps into the implementation.
// So for those of you who are not familiar with the `std::variant`, you can consider
// it as a union(a type-safe union). And line `std::variant<Markdown, HTML>`, suggest 
// that you can use/assign/access either `Markdown` or `HTML` at a time.
//
// And [Modern C++](http://www.vishalchovatiya.com/21-new-features-of-modern-cpp-to-use-in-your-project/) 
// provides us `std::visit` which accept callable i.e. `DocumentPrinter` in our case 
// having overloaded function operator and `std::variant` as the second argument. 
// You also make use of [lambda functions](http://www.vishalchovatiya.com/learn-lambda-function-in-cpp-with-example/) rather using functor i.e. `DocumentPrinter`.
