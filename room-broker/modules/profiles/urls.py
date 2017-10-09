from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^register/$', '', name='register'),
    url(r'^register/complete/$', 'simplesite.views.registration_complete', name='registration_complete'),
    url(r'^logout/$', 'django.contrib.auth.views.logout', {'next_page': '/'}),
    ]