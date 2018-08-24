// Created by gordonzu on 8/20/18.


class Vector {
public:
    Vector() {}

    Vector(const Vector& x) {
        vec.clear();
        s = 0;
        for (auto& item : x.vec) {
            vec.emplace_back(item);
            ++s;
        }
    }

   Vector& operator=(const Vector& x) {
        if (this == &x) return *this;

        for (auto& item : x.vec) {
            vec.emplace_back(item);
            ++s;
        }
    }

    bool operator==(const Vector& x) {
        if (s != x.s) return false;

        for (auto& item : x.vec) {
            if (vec[--s] != item) return false;
            --s;
        }
        return true;
    }

    bool operator<(const Vector& x) {
        if (s < x.s) return true;

        for (auto& item : x.vec) {
            if (vec[--s] < item) return true;
        }
        return false;
    }

    BaseObject& operator[](int i) {
        return vec[i]; 
    }

    BaseObject& emplace_back(const BaseObject& x) {
        return vec.emplace_back(x);
    }

    size_t size() {
        return vec.size();
    }

    void clear() {
        return vec.clear();
    }

	friend std::ostream& operator<<(std::ostream& out, const Vector& x) {
        out << "<Vector>" << std::endl;
        for (const auto& x : x.vec) {
            out << std::string(2, ' ') << x << std::endl;
        }
        out << "</Vector>";
        return out;
    }
 
private:
    size_t s;
    std::vector<BaseObject> vec;


};


