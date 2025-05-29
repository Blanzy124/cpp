import sys
sys.path.append(r"C:/Users/samue/AppData/Local/Programs/Python/Python313/Lib/site-packages")
import aiohttp;
import asyncio;

async def GETREQ(URL):
 async with aiohttp.ClientSession() as session:
  async with session.get(URL) as res:
   return await res.json()


async def main():
 print( await GETREQ("https://blanzynetwork.org:8443"))
asyncio.run(main())