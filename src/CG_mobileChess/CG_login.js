// The logo width and height is 1/2 of the height when in portrait
// and 1/3 of the height when in landscape.
function getLogoSize()
{
    return background.width > background.height ? background.height * 0.33 : background.height / 2
}

// The individual control height is 1/15 of the height when in portrait
// and (2/3) * (1/8) = apprx 8.33% in landscape.
function getControlHeight()
{
    return background.width > background.height ? background.height * 0.0833 : background.height / 15
}

// The individual control width is 90% of the smallest orientation.
function getControlWidth()
{
    return getSmallestOrientation() * 0.9
}
