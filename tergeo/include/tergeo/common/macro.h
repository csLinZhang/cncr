/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                   A MI TUO LE GE FO                  |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                   GOD BLESS NO BUGS!!                 
 *                                                      
 *                        _ooOoo_                       
 *                       o8888888o                      
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                    ____/'___'\____
 *                  .'  \\|     |//  '. 
 *                 /  \\|||  :  |||//  \
 *                /  _||||| -:- |||||_  \
 *                |   | \\\  -  /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  `-`  __/-.  /
 *              ___`..'   /--.--\   `..'___
 *           ."" '<  `.___\_<|>_/___.'  >' "".
 *          | | :  `-\`.;` \ _ / ';.`/- ` : | |
 *          \  \ `-.  \_ __ \ / __ _/  .-` /  /
 *     ======`-.____`-.__\_______/ __.-`___.-'====== 
 *                       `=-----=' 
 *     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef _TERGEO_COMMON_MACRO_H_
#define _TERGEO_COMMON_MACRO_H_
#include <memory>

#define DISALLOW_COPY_AND_ASSIGN(class_name)           \
    private:                                           \
        class_name(const class_name &);                \
        class_name &operator=(const class_name &);

#define DISALLOW_IMPLICIT_CONSTRUCTORS(class_name)     \
    private:                                           \
        class_name();                                  \
        DISALLOW_COPY_AND_ASSIGN(class_name);

#define DECLARE_SINGLETON(class_name)                 \
    public:                                           \
        static class_name *Instance() {               \
            static class_name s_instance;             \
            return &s_instance;                       \
        }                                             \
        DISALLOW_IMPLICIT_CONSTRUCTORS(class_name)      

#define DECLARE_SHARED_PTR(class_name)                \
    typedef std::shared_ptr<class_name> Ptr;


#define DECLARE_UNIQUE_PTR(class_name)                \
    typedef std::unique_ptr<class_name> Ptr;

#define DECLARE_DEFAULT_STRUCTOR(class_name)               \
    public:                                                \
        class_name() = default;                            \
        virtual ~class_name() = default;     
#endif
