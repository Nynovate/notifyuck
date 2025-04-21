# notifyuck
Notifyuck is a C program that can be used to create a notification center for Eww.
I've saw a lot of cool ricing on Hyprland with Eww, that got their own notification center.
Implementing it can be quite complex specially for people not really used with script and unix.
So I decided to create this simple user-friendly program so you can also easily implement a notification center in your rice!!!

## Dependencies
You need to have dunst as your notification manager. Other notification manager are not supported for the moment.
Obviously you need to have Eww installed also.

## Example Of Output
With this as template:
<pre>``` yuck
(box	:class "notif_box_{11}"
:orientation "h"
			:space-evenly false
			(box	:class "box"
					:orientation "h"
					:space-evenly false
					:width 550
					(box	:class "icon_notification"
							:halign "center"
							:valign "center"
							:style "background-image: url('{6}');"
					)
					(box	:class "box"
							:orientation "v"
							:space-evenly false
							(label	:class "notif_label"
									:halign "start"
									:markup "{2} from {3}"
									:style "font-size: 16px; font-weight: bold; padding-top: 12px;"
							)
							(label	:class "notif_label"
									:halign "start"
									:markup "{0}"
									:style "font-size: 12px; padding-top: 4px;"
							)
					)
			)
			(button	:class "notif_button_label"
		 			:onclick "dunstctl history-rm \{7}"
		 			:halign "end"
		 			"X"
			)
	)```
</pre>
We can get the following result:
![Output Example](images/output_example.png)
