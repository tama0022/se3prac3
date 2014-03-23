int combine_tiles(int length,int *line,int offset);
int tilt_through_empty_space(int length, int *line);

/*
  Takes a list of <length> integers, and attempts to shift them left
  according to the rules of 2048.

  The shift is always to the left.  If the caller wants to shift to
  the right instead, they should reverse the list order.

  This means pairs of identical numbers with no other number inbetween
  get merged together.  But the same tile may not be involved in more
  than one merge.
*/

int tilt_line_left(int length,int *line)
{
  // make sure vector length is sensible
  if (length<1||length>255) return -1;

  // Beginning at the left, try to move the rest of the tiles
  // left. No combining yet.
  for(i=0;i<(length-1);i++)
    tilt_through_empty_space(length,&line[i]);
  
  // Combine pairs
  for(i=0;i<(length-1);i++) {
    if (line[i]==line[i+1]) {
      combine_tiles(length,line,i);
    }
  }

  return 0;
}

int combine_tiles(int length,int *line,int offset)
{
  int i;
  // calculate sum
  line[offset]+=line[offset+1];
  // shift tiles left
  for(i=offset+1;i<(length-1);i++) line[i]=line[i+1];
  // insert empty tile on right edge
  line[length-1]=0;
  return 0;
}

int tilt_through_empty_space(int length, int *line)
{
  while(!line[0]) {
    int i;
    for(i=0;i<(length-1);i++) line[i]=line[i+1];
  }
  return 0;
}