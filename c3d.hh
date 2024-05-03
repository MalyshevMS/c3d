#include <string>

using namespace std;
using namespace c3d::functions;
using namespace c3d::constants;


namespace c3d {
    namespace constants {
        string X = "x";
        string Y = "y";
        string Z = "z";
        string ALL_AXIS = "ax+";

        string MULTIPLY = "MULTIPLY";
        string ADD = "ADD";
        string SET = "SET";

        string XY = "xy";
        string XZ = "xz";
        string ZY = "zy";

        short X_BORDER = 0;
        short Y_BORDER = 1;
        short Z_BORDER = 2;

        short X_COORD = 0;
        short Y_COORD = 1;
        short Z_COORD = 2;

        short SIZE_X = 0;
        short SIZE_Y = 1;
        short SIZE_Z = 2;

        enum errcode {
            BorderError = 406
        };
    }

    namespace functions {
        template <typename T_seq>
        void print(T_seq seq = "", string end = "\n") {
            cout << seq << end;
        }

        template <typename T_seq, typename T_sep>
        void print(T_seq seq[], int len, T_sep sep = "", string end = "\n") {
            for (int i = 0; i < len; i++) {
                if (i < len - 1) {
                    cout << seq[i] << sep;
                } else {
                    cout << seq[i] << end;
                }
            }
        }

        template <typename T_return, typename T_promt>
        T_return input(T_promt promt) {
            cout << promt;
            T_return res;
            res << cin;
            cout << endl;
            return res;
        }

        template <typename T_err>
        void printerr(int code, T_err err) {
            cerr << "Error " << code << ": " << err << endl;
        }

        template <typename T_err>
        void printerr(int code, T_err err[], int len) {
            cerr << "Error " << code << ": ";
            for (int i = 0; i < len; i++) {
                cerr << err[i];
            }
            cerr << endl;    
        }

        int* range_raw(int stop) {
            int arr[stop];
            int *ptr = arr;
            for (int i; i < stop; i++) {
                *(ptr + i) = i;
            }
            return ptr;
        }

        int* range_raw(int start, int stop) {
            int arr[stop - start];
            int *ptr = arr;
            for (int i = start; i < stop; i++) {
                *(ptr + (i - start)) = i;
            }
            return ptr;
        }

        int auto_range_el(int len, int el) {
            return *(range_raw(len) + el);
        }

        int range_el(int* rang, int el) {
            return *(rang + el);
        }

        bool in_range(int elem, int range_len) {
            for (int i = 0; i < range_len; i++) {
                if (elem == auto_range_el(range_len, i)) {
                    return true;
                } 
            }

            return false;    
        }

        bool in_range(int elem, int* rnge, int len) {
            for (int i = 0; i < len; i++) {
                if (elem == range_el(rnge, i)) {
                    return true;
                } 
            }

            return false;    
        }

        bool in_arr(int elem, int* arr, int len) {
            for (int i = 0; i < len; i++) {
                if (elem == *(arr + i)) {
                    return true;
                } 
            }

            return false;    
        }
    }

    class Volume {
    // private:
    public:
        unsigned int border[3] = {0, 0, 0};

        Volume(unsigned int border_x = 0, unsigned int border_y = 0, unsigned int border_z = 0) {
            this->border[X_BORDER] = border_x;
            this->border[Y_BORDER] = border_y;
            this->border[Z_BORDER] = border_z;

        };

        unsigned int *get_border() {
            if (this->border[X_BORDER] > 0 && this->border[Y_BORDER] > 0 && this->border[Z_BORDER] > 0) { 
                return this->border;
            }
            else {
                printerr <string> (errcode::BorderError, "cannot get NULL border");
                exit(errcode::BorderError);
            }
        };

        void border_edit(string axis = ALL_AXIS, int value = 0) {
            if (axis == X) {
                this->border[X_BORDER] = value;
            } 
            else if (axis == Y) {
                this->border[Y_BORDER] = value;
            }
            else if (axis == Z) {
                this->border[Z_BORDER] = value;
            }
            else if (axis == ALL_AXIS) {
                this->border[X_BORDER] = value;
                this->border[Y_BORDER] = value;
                this->border[Z_BORDER] = value;
            }
        };
    };

    class Box {
    private:
        int x = 0;
        int y = 0;
        int z = 0;

        int size_x = 1;
        int size_y = 1;
        int size_z = 1;

        unsigned int sizes[3] = {1, 1, 1};
        unsigned int coords[3] = {0, 0, 0};

        Volume space;
        string name;
    public:
        Box(Volume space, int x = 0, int y = 0, int z = 0, int size_x = 1, int size_y = 1, int size_z = 1, string name = "") {
            if ((size_x + x <= space.border[X_BORDER] && size_y + y <= space.border[Y_BORDER] && size_z + z <= space.border[Z_BORDER]) && (x >= 0 && y >= 0 && z >= 0)) {
                this->x = x;
                this->y = y;
                this->z = z;

                this->size_x = size_x;
                this->size_y = size_y;
                this->size_z = size_z;

                this->coords[X_COORD] = this->x;
                this->coords[Y_COORD] = this->y;
                this->coords[Z_COORD] = this->z;

                this->sizes[SIZE_X] = this->size_x;
                this->sizes[SIZE_Y] = this->size_y;
                this->sizes[SIZE_Z] = this->size_z;

                this->space = space;
                this->name = name;
            } else {
                string errmsg[] = {"cannot create box '", name, "': box out of border"};
                printerr <string> (errcode::BorderError, errmsg, 3);
                exit(errcode::BorderError);
            }
        };

        unsigned int* get_coords() {
            return this->coords;
        };

        unsigned int* get_size() {
            return this->sizes;
        };

        void display(string plane = XY, char box_fill = '#', char empty_fill = '.', string dist = " ") {
            if (plane == XY) {
                for (int i = 0; i < this->space.border[Y_BORDER]; i++) {
                    for (int j = 0; j < this->space.border[X_BORDER]; j++) {
                        int stop1 = this->size_y + this->y;
                        int stop2 = this->size_x + this->x;
                        if (in_range(i, range_raw(this->y, (this->size_y + this->y)), ((this->size_y + this->y) - this->y)) == true && in_range(j, range_raw(this->x, (this->size_x + this->x)), ((this->size_x + this->x) - this->x)) == true) {
                            print <char> (box_fill, dist);
                        }
                        // else {
                        //     print <char> (empty_fill, dist);
                        // }
                    }
                    print <string> ();
                }
                
            }
            else if (plane == XZ) {

            }
            else if (plane == ZY) {

            }
        };
    };
}