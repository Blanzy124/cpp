import sys
sys.path.append(r"C:/Users/samue/AppData/Local/Programs/Python/Python313/Lib/site-packages")

from OPY import httpsR
from OPY import web_s
import aiohttp;
import asyncio;
import ssl

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
                  ws_W = web_s(httpr._url, httpr._JWT, False)
                  await ws_W.ws_connection()
               case 2:
                  pass
            
            

   

   
asyncio.run(main())

