
#ifndef IVIEW_H_
#define IVIEW_H_

namespace connectfour {

    class IView {
    public:
        virtual void update() = 0;

        bool operator ==(const IView &other) const {
            return std::addressof(*this) == std::addressof(other);
        };
        
        bool operator !=(const IView &other) const {
            return !(*this == other);
        };
    };
}

#endif
