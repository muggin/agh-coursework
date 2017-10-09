from django.conf.urls import url
from modules.reservations import views

__author__ = 'O10'

urlpatterns = [

    url(r'^$', views.ReservationList.as_view(), name='reservation'),
    url(r'^add/$', views.ReservationCreateView.as_view(), name='reservation_create'),

]