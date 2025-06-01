import sys
sys.path.append(r"C:/Users/samue/AppData/Local/Programs/Python/Python313/Lib/site-packages")


import aiohttp;
import asyncio;
import ssl
import json



def validatedJson(j):
  try:
    json.loads(j)
    return True
  except (json.JSONDecodeError, TypeError):
    return False
      

class httpsR:
 cookieId = None
 JWT = None
 def __init__(self, user_name, user_password, url, secure):
  self._user_name = user_name
  self._user_password = user_password
  self._url = url
  self._cookieId = None
  self._JWT = None
  self._secure = secure

  @property
  def url(self):
    return self._url

  @property
  def cookieId(self):
   return self._cookieId
  
  @property
  def JWT(self):
   return self._JWT
  
  
 async def secureSetUp(self):
   if self._secure == False:
    req_secure = ssl.create_default_context()
    req_secure.check_hostname = False
    req_secure.verify_mode = ssl.CERT_NONE
    return req_secure
   else:
     req_secure = ssl.create_default_context()
     return None
  
 async def logIn(self):
    print("Login launched")
    headers = {"Content-Type": "application/json"}
    body = { "userName" : self._user_name, "userPassword" : self._user_password}
    async with aiohttp.ClientSession(self._url) as session:
      async with session.post("/users/login", data=json.dumps(body) ,headers=headers, ssl= await self.secureSetUp()) as res:
        print("Requesting")
        if res.status == 200:
          resp = await res.json()
          if resp['ok'] != True:
            print(resp)
            return False
          else:
            self._cookieId = resp["data"]['cookieId']
            print("Login succes")
            return True
            
 async def JWTsetUp(self):
   print("Requesting JWT...")
   headers = {"Content-Type": "application/json"}
   body = { "cookieId": self._cookieId }
   async with aiohttp.ClientSession(self._url) as session:
     async with session.post("/tokens/jwtrefresh", data=json.dumps(body), headers=headers, ssl= await self.secureSetUp()) as res:
       if res.status == 200:
         resp = await res.json()
         if validatedJson(resp) == True: 
          if resp['ok'] == False:
            print(resp)
            return False
         else:
            self._JWT = resp
            return True
       else:
         print("Error: ", resp)
         
class web_s:
  _ws_o = None
  def __init__(self, url , JWT, secure):
    self._url = url
    self._JWT = JWT
    self._secure = secure
    self._from = None
    self._to = None
  
  
  @property
  def JWT(self):
    return self._JWT
  
  async def secureSetUp(self):
    if self._secure == False:
     req_secure = ssl.create_default_context()
     req_secure.check_hostname = False
     req_secure.verify_mode = ssl.CERT_NONE
     return req_secure
    else:
      req_secure = ssl.create_default_context()
      return None
  
  async def ws_connection(self, input):
    async with aiohttp.ClientSession(self._url) as session:
      async with session.ws_connect(f"/foo?token={self.JWT}", ssl= await self.secureSetUp()) as ws:
        
        
        async def receiver():
            async for msg in ws:
                if msg.type == aiohttp.WSMsgType.TEXT:
                    print("Mensaje del servidor:", msg)
                    msgJ = json.loads(msg.data)
                    print(msgJ)
                    self._to = msgJ["from"]
                    self._from = msgJ["to"]
                elif msg.type == aiohttp.WSMsgType.CLOSED:
                    print("WebSocket cerrado por el servidor.")
                    break
                elif msg.type == aiohttp.WSMsgType.ERROR:
                    print("Error en WebSocket:", msg)
                    break
        recv_task = asyncio.create_task(receiver())

        while True:
            data = await input.event_queue.get()
            body = { "message": data, "from": self._from,  "to": self._to}
            await ws.send_str(json.dumps(body))
            print("Evento enviado:", json.dumps(body))
        await recv_task


    
        