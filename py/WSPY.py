#import sys
#sys.path.append(r"C:/Users/samue/AppData/Local/Programs/Python/Python313/Lib/site-packages")

from OPY import httpsR
from OPY import web_s
import aiohttp;
import asyncio;
import ssl
import pygame

class control:
   _contronModel = None
   
   
   
   
   def __init__(self, status):
      self.status = status
      self.event_queue = asyncio.Queue()

         
   async def actionTake(self):
      pygame.init()
      pygame.joystick.init()

      if pygame.joystick.get_count() == 0:
         print("no controller conected")
         return -1

      mando = pygame.joystick.Joystick(0)
      mando.init()
      self.contronModel = mando.get_name()
      exitB = 0
      while exitB != 10:
         for enventm in pygame.event.get():
            if enventm.type == pygame.JOYBUTTONDOWN:
               exitB = enventm.button
               action = f"Button: {enventm.button} pressed"
               print(action)
               await self.event_queue.put(action)
               

            if enventm.type == pygame.JOYBUTTONUP:
               exitB = enventm.button
               action = f"Button: {enventm.button} unpressed"
               print(action)
               await self.event_queue.put(action)
         await asyncio.sleep(0.01)

            
async def main():
   httpr = httpsR("cpp", "cpp2005", "https://localhost:8443", False)
   if await httpr.logIn() != True:
      print("Error, closing")
      exit()
      print("cookie: ",httpr._cookieId)
   else:
      if await httpr.JWTsetUp() != True:
         print("Error setting JWT")
      else:   
         print("Save JWT succes")
         option = None
         while option != 0:
            option = int(input("selection"))
            match option:
               case 0:
                  print("Closing script")
                  exit()
               case 1:
                  act = control(1)
                  ws_W = web_s(httpr._url, httpr._JWT, False)
                  await asyncio.gather(
                     act.actionTake(),
                     ws_W.ws_connection(act)
                  )
               case 2:
                  pass
            
            

   

   
asyncio.run(main())

