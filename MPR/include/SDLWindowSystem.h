/////////////////////////////////////////////////////////////
// File  : SDLSystem.h                                     //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : SDL implementations such as creating a window   //
//         and event handling                              //
/////////////////////////////////////////////////////////////

#ifndef SDLWINDOW_H
#define SDLWINDOW_H

namespace Framework
{
  class SDLWindowSystem : public ISystem 
  {
    public:
    SDLWindowSystem(int width, int height);
    ~SDLWindowSystem();
 
    void Activate();
      void Event(SDL_Event* Event);
    int GetWidth();
    int GetHeight();
    
    //inherited functions
    virtual void Initialize();
    virtual void Update(float dt);//Update the system every frame
    virtual std::string GetName() {return "SDLWindowSystem";}
    virtual void RecieveMessage(Message* message);

    private:
      void ToggleFullScreen(bool enable);
    int Height_,Width_;
    SDL_Window   *Window_;
    SDL_GLContext Context_;
  };

  //A global pointer to the instance of the core
  extern SDLWindowSystem* WINDOW;

} //namespace



#endif