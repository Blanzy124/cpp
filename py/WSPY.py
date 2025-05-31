import sys
sys.path.append(r"C:/Users/samue/AppData/Local/Programs/Python/Python313/Lib/site-packages")

from OPY import httpsR

import aiohttp;
import asyncio;
import ssl

async def main():
   httpr = httpsR("cpp", "cpp2005", "https://localhost:8443", False)
   if await httpr.logIn() != True:
      print("Error, closing")
      exit()
   else:
      print("cookie: ",httpr._cookieId)
      await httpr.JWTsetUp()
      print(httpr._JWT)
asyncio.run(main())












async def GETREQ(URL, req_secure):
 async with aiohttp.ClientSession() as session:
  async with session.get(URL, ssl=req_secure) as res:
   resp = await res.json()
   
   return resp[0]['message']


async def mainR():
   req_secure = ssl.create_default_context()
   req_secure.check_hostname = False
   req_secure.verify_mode = ssl.CERT_NONE
   print( await GETREQ("https://localhost:8443", req_secure))
#asyncio.run(main())