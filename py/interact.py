import dearpygui.dearpygui as dpg

dpg.create_context()

class contar:
 def __init__(self):
    self._times = 0
 
 @property
 def times(self):
  return self._times

 def set_times(self):
  self._times =  self._times + 1

count = contar()

def change_text(sender, app_data):
    dpg.set_value("text_item", f"Mouse Button: {app_data[0]}, Down Time: {app_data[1]} seconds")

def showCount(sender, app_data):
    count.set_times()
    dpg.set_value("counter", f"Pressed times: {count.times}")
 

with dpg.handler_registry():
    dpg.add_mouse_down_handler(callback=change_text)
    
with dpg.item_handler_registry(tag="counterCall") as handler:
    dpg.add_item_clicked_handler(callback=showCount)

with dpg.window(width=500, height=300):
    dpg.add_text("Press any mouse button", tag="text_item")
    dpg.add_text("This only show how many time any button mouse was pressed", tag="counter")
    
dpg.bind_item_handler_registry("counter", "counterCall")

dpg.create_viewport(title='Custom Title', width=800, height=600)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.start_dearpygui()
dpg.destroy_context()