from django.contrib import admin

# Register your models here.
from modules.reservations.models import Reservation

admin.site.register(Reservation)