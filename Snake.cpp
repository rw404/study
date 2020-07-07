#include <iostream>
#include <stack>
#include <string>

class Snake
{
  private:
          std::string color;
          std::string username;

  public:
          std::stack <char> body;
          int length;

          //constructor
          Snake(const std::string* user, const std::string color_user)
          : username(new char[std::strlen(user)+1]), color(new char[std::strlen(color_user)])
          {
              length = 1;
              body.push(1);
              std::strcpy(username, user);
              std::strcpy(color, color_user);
          }
          
          //distructor
          ~Snake()
          {
              while(!body.empty())
              {
                body.pop();
                --length;
              }
              delete[] username;
              delete[] color;
          }

          //copy_constructor
          Snake(const Snake& other)//friend for private
          {
            username = new char[std::strlen(other.username) + 1];
            color    = new char[std::strlen(other.color) + 1];
            std::strcpy(username, other.username);
            std::strcpy(color, other.color);
            length   = other.length;
            
            auto std::stack <char> tmp;
            while(!(other.body).empty()) 
            {
              tmp.push((other.body).pop());
            }   
            while(!tmp.empty())
            {
              body.push(tmp.pop());
              (other.body).push(body.top());
            }            
          }

          //move_constructor
          Snake(Snake&& mover):length(mover.length),color(mover.color),username(mover.username)
          {
            mover.username = nullptr;
            mover.color    = nullptr;
            mover.length   = 0;
            while(!(other.body).empty()) body.push((other.body).pop());
          }

          //copy_assigment
          Snake& operator=(const Snake& other)
          {
            if(this  == &other)
              return *this;

            delete[] username;
            delete[] color;
            username = new char[std::strlen(other.username) + 1];
            std::strcpy(username, other.username);
            color    = new char[std::strlen(other.color) + 1];
            std::strcpy(color, other.color);
            length   = other.length;

            while(!body.empty()) body.pop();

            auto std::stack <char> tmp;
            while(!(other.body).empty()) 
            {
              tmp.push((other.body).pop());
            }   
            while(!tmp.empty())
            {
              body.push(tmp.pop());
              (other.body).push(body.top());
            }

            return *this;
          }

          //move_assigment
          Snake& operator=(Snake&& other) noexcept
          {
            if(this == other) return *this;

            delete[] username;
            delete[] color;
            
            username      = other.username;
            that.username = nullptr;
            color         = other.color;
            other.color   = nullptr;
            length        = other.length;
            other.length  = 0;

            while(!body.empty()) body.pop();

            while(!(other.body).empty()) body.push((other.body).pop());
            
            return *this;
          }
};


