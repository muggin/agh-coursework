from django.contrib import admin
from modules.accommodations.models import Accommodation, Listing, Photo

# Register your models here.
admin.site.register(Accommodation)
admin.site.register(Listing)
admin.site.register(Photo)
