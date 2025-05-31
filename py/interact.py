import sys
sys.path.append(r"C:/Users/samue/AppData/Local/Programs/Python/Python313/Lib/site-packages")

from OPY import httpsR
from OPY import web_s
import aiohttp;
import asyncio;
import ssl



async def main():
 option = None
 while option != 0:
  option = int(input("selection"))
  match option:
   case 0:
    print("Closing script")
   case 1:
    