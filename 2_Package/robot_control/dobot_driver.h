
{
dobot mydobot;
  setpos(ArmPose *pos)
{
  mydobot.sendpos(pos->x , pos->y, pos->z , pos->r)
}


}
