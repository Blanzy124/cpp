from reuse import validatedJson

class httpsR:
 def __init__(self, user_name, user_password, url, secure):
  self._user_name = user_name
  self._user_password = user_password
  self._url = url
  self._secure = secure
  self._JWT = None
  self._cookieId = None
  
  